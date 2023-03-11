#include "Lithosphere.h"

#include <cassert>

#include "Plate.h"

#include <cfloat>
#include <cstdlib>
#include <vector>
#include "../DiamondSquare.h"

#define BOOL_REGENERATE_CRUST    1


using namespace std;

/**
 * Wrapper for growing plate from a seed. Contains plate's dimensions.
 *
 * Used exclusively in plate creation phase.
 */
RandomEngine Lithosphere::rand {};

class plateArea {
public:
	vector<size_t> border; ///< Plate's unprocessed border pixels.
	size_t btm; ///< Most bottom pixel of plate.
	size_t lft; ///< Most left pixel of plate.
	size_t rgt; ///< Most right pixel of plate.
	size_t top; ///< Most top pixel of plate.
	size_t wdt; ///< Width of area in pixels.
	size_t hgt; ///< Height of area in pixels.
};

static const float SQRDMD_ROUGHNESS = 0.5f;

static const float BUOYANCY_BONUS_X = 3;
static const size_t MAX_BUOYANCY_AGE = 20;
static const float MULINV_MAX_BUOYANCY_AGE = 1.0f / (float)MAX_BUOYANCY_AGE;


std::vector<float> squareDiamondAdaptater(const size_t map_side_length, const unsigned seed, const double roughness){
    DiamondSquare ds = DiamondSquare(map_side_length+1, seed, roughness);
    auto dsMap = ds.execute();
    std::vector<float> rtn (map_side_length*map_side_length);

    int border = -1;
    for (size_t i = 0; i < rtn.size(); ++i)
    {
        if (i % map_side_length == 0)
        {
            border++;
        }
        rtn[i] = dsMap->array[i+border];

    }
    return rtn;

}

Lithosphere::Lithosphere(size_t map_side_length, float sea_level,
	size_t _erosion_period, float _folding_ratio, size_t aggr_ratio_abs,
	float aggr_ratio_rel)
	:
	aggr_overlap_abs(aggr_ratio_abs),
	aggr_overlap_rel(aggr_ratio_rel),
	erosion_period(_erosion_period),
	folding_ratio(_folding_ratio),
	map_side(map_side_length),
	num_plates(0) {
	const size_t aera = (map_side) * (map_side);



	auto tmp = squareDiamondAdaptater(map_side, rand(), SQRDMD_ROUGHNESS);
	float lowest = tmp[0], highest = tmp[0];
	for (size_t i = 1; i < aera; ++i) {
		lowest = lowest < tmp[i] ? lowest : tmp[i];
		highest = highest > tmp[i] ? highest : tmp[i];
	}

	for (size_t i = 0; i < aera; ++i) // Scale to [0 ... 1]
		tmp[i] = (tmp[i] - lowest) / (highest - lowest);

	float sea_threshold = 0.5;
	float th_step = 0.5;

	// Find the actual value in height map that produces the continent-sea
	// ratio defined be "sea_level".
	while (th_step > 0.01) {
		size_t count = 0;
		for (size_t i = 0; i < aera; ++i)
			count += (tmp[i] < sea_threshold);

		th_step *= 0.5;
		if (count / (float)aera < sea_level)
			sea_threshold += th_step;
		else
			sea_threshold -= th_step;
	}

	sea_level = sea_threshold;
	for (size_t i = 0; i < aera; ++i) // Genesis 1:9-10.
	{
		tmp[i] = (tmp[i] > sea_level) *
			(tmp[i] + CONTINENTAL_BASE) +
			(tmp[i] <= sea_level) * OCEANIC_BASE;
	}

	heightMap.resize(map_side * map_side);
	for (size_t i = 0; i < (map_side * map_side); ++i)
	{
		heightMap[i] = tmp[i];
	}

	ownerMap = std::vector<size_t>(map_side * map_side);
}

Lithosphere::~Lithosphere() noexcept = default;

void Lithosphere::createPlates(size_t num_plates) throw() {
	const size_t map_area = map_side * map_side;
	this->num_plates = num_plates;

	std::vector <plateCollision> vec;
	vec.reserve(map_side * 4); // == map's circumference.

	collisions.reserve(num_plates);
	subductions.reserve(num_plates);

	for (size_t i = 0; i < num_plates; ++i) {
		collisions.push_back(vec);
		subductions.push_back(vec);
	}

	// Initialize "Free plate center position" lookup table.
	// This way two plate centers will never be identical.
	for (size_t i = 0; i < map_area; ++i)
		ownerMap[i] = i;

	// Select N plate centers from the global map.
	std::vector<plateArea> area{ num_plates };
	for (size_t i = 0; i < num_plates; ++i) {
		// Randomly select an unused plate origin.
		const size_t p = ownerMap[(size_t)rand() % (map_area - i)];
		const size_t y = p / map_side;
		const size_t x = p - y * map_side;

		area[i].lft = area[i].rgt = x; // Save origin...
		area[i].top = area[i].btm = y;
		area[i].wdt = area[i].hgt = 1;

		area[i].border.reserve(8);
		area[i].border.push_back(p); // ...and mark it as border.

		// Overwrite used entry with last unused entry in array.
		ownerMap[p] = ownerMap[map_area - i - 1];
	}

	std::fill(ownerMap.begin(), ownerMap.end(), 255);

	// "Grow" plates from their origins until surface is fully populated.
	size_t max_border = 1;
	size_t i;
	while (max_border)
		for (max_border = i = 0; i < num_plates; ++i) {
			const size_t N = area[i].border.size();
			max_border = max_border > N ? max_border : N;

			if (N == 0)
				continue;

			const size_t j = rand() % N;
			const size_t p = area[i].border[j];
			const size_t cy = p / map_side;
			const size_t cx = p - cy * map_side;

			const size_t lft = cx > 0 ? cx - 1 : map_side - 1;
			const size_t rgt = cx < map_side - 1 ? cx + 1 : 0;
			const size_t top = cy > 0 ? cy - 1 : map_side - 1;
			const size_t btm = cy < map_side - 1 ? cy + 1 : 0;

			const size_t n = top * map_side + cx; // North.
			const size_t s = btm * map_side + cx; // South.
			const size_t w = cy * map_side + lft; // West.
			const size_t e = cy * map_side + rgt; // East.

			if (ownerMap[n] >= num_plates) {
				ownerMap[n] = i;
				area[i].border.push_back(n);

				if (area[i].top == ((top + 1) & (map_side - 1))) {
					area[i].top = top;
					area[i].hgt++;
				}
			}

			if (ownerMap[s] >= num_plates) {
				ownerMap[s] = i;
				area[i].border.push_back(s);

				if (btm == ((area[i].btm + 1) & (map_side - 1))) {
					area[i].btm = btm;
					area[i].hgt++;
				}
			}

			if (ownerMap[w] >= num_plates) {
				ownerMap[w] = i;
				area[i].border.push_back(w);

				if (area[i].lft == ((lft + 1) & (map_side - 1))) {
					area[i].lft = lft;
					area[i].wdt++;
				}
			}

			if (ownerMap[e] >= num_plates) {
				ownerMap[e] = i;
				area[i].border.push_back(e);

				if (rgt == ((area[i].rgt + 1) & (map_side - 1))) {
					area[i].rgt = rgt;
					area[i].wdt++;
				}
			}

			// Overwrite processed point with unprocessed one.
			area[i].border[j] = area[i].border.back();
			area[i].border.pop_back();
		}
	plates.clear();
	plates.reserve(num_plates);

	// Extract and create plates from initial terrain.
	for (size_t i = 0; i < num_plates; ++i) {
		area[i].wdt = area[i].wdt < map_side ? area[i].wdt : map_side - 1;
		area[i].hgt = area[i].hgt < map_side ? area[i].hgt : map_side - 1;

		const size_t x0 = area[i].lft;
		const size_t x1 = 1 + x0 + area[i].wdt;
		const size_t y0 = area[i].top;
		const size_t y1 = 1 + y0 + area[i].hgt;
		const size_t width = x1 - x0;
		const size_t height = y1 - y0;
		float* plt = new float[width * height];

		// Copy plate's height data from global map into local map.
		for (size_t y = y0, j = 0; y < y1; ++y)
			for (size_t x = x0; x < x1; ++x, ++j) {
				size_t k = (y & (map_side - 1)) * map_side +
					(x & (map_side - 1));
				plt[j] = heightMap[k] * (ownerMap[k] == i);
			}

		// Create plate.
		plates.emplace_back(plt, width, height, x0, y0, i, map_side);
		delete[] plt;
	}

	currentAge = MAX_BUOYANCY_AGE + num_plates;
	peak_Ek = 0;
	last_coll_count = 0;

	calcEnergy();
}

size_t Lithosphere::getPlateCount() const throw() {
	return num_plates;
}

const vector<float> Lithosphere::getTopography() const throw() {
	return heightMap;
}

vector<float>& Lithosphere::freeTopography(){
    return heightMap;
}

void Lithosphere::calcEnergy()
{
	totalVelocity = 0;
	systemKineticEnergy = 0;
	for (size_t i = 0; i < num_plates; ++i) {
		totalVelocity += plates[i].getVelocity();
		systemKineticEnergy += plates[i].getMomentum();
	}

	if (systemKineticEnergy > peak_Ek)
		peak_Ek = systemKineticEnergy;
}

void Lithosphere::update() throw() {


	const size_t map_area = map_side * map_side;
	const std::vector<size_t> prev_ownerMap{ std::move(ownerMap) };
	ageMap.resize(map_area);
	ownerMap = std::vector<size_t>(map_area);

	// Realize accumulated external forces to each plate.
	for (size_t i = 0; i < num_plates; ++i) {
		plates[i].resetSegments(); // not optimal, calculate segment is heavy

		if (erosion_period > 0 && currentAge % erosion_period == 0)
			plates[i].erode(CONTINENTAL_BASE);

		plates[i].move();
	}

	size_t oceanic_collisions = 0;
	size_t continental_collisions = 0;

	// Update height and plate index maps.
	// Doing it plate by plate is much faster than doing it index wise:
	// Each plate's map's memory area is accessed sequentially and only
	// once as opposed to calculating "num_plates" indices within plate
	// maps in order to find out which plate(s) own current location.
	std::fill(heightMap.begin(), heightMap.end(), 0.0f);
	std::fill(ownerMap.begin(), ownerMap.end(), 255.0f);

	for (size_t i = 0; i < num_plates; ++i) {
		const size_t x0 = static_cast<size_t>(plates[i].getLeft());
		const size_t y0 = static_cast<size_t>(plates[i].getTop());
		const size_t x1 = x0 + plates[i].getWidth();
		const size_t y1 = y0 + plates[i].getHeight();

		const float* this_map = plates[i].getMap();
		const std::vector<size_t> this_age = plates[i].getAge();

		// Copy first part of plate onto world map.
		for (size_t y = y0, j = 0; y < y1; ++y)
			for (size_t x = x0; x < x1; ++x, ++j) {
				const size_t x_mod = x % map_side;
				const size_t y_mod = y % map_side;

				const size_t index_coord = y_mod * map_side + x_mod;

				if (this_map[j] < 2 * FLT_EPSILON) // No crust here...
					continue;

				if (ownerMap[index_coord] >= num_plates) // No one here yet?
				{
					// This plate becomes the "owner" of current location
					// if it is the first plate to have crust on it.
					heightMap[index_coord] = this_map[j];
					ownerMap[index_coord] = i;
					ageMap[index_coord] = this_age[j];

					continue;
				}

				// DO NOT ACCEPT HEIGHT EQUALITY! Equality leads to subduction
				// of shore that 's barely above sea level. It's a lot less
				// serious problem to treat very shallow waters as continent...
				const bool prev_is_oceanic = heightMap[index_coord] < CONTINENTAL_BASE;
				const bool this_is_oceanic = this_map[j] < CONTINENTAL_BASE;
				{//oceanic collision
					const size_t prev_timestamp = plates[ownerMap[index_coord]].getCrustTimestamp(x_mod, y_mod);
					const size_t this_timestamp = this_age[j];

					const bool cond1 = heightMap[index_coord] > this_map[j];
					//almos equal
					const bool cond2 = heightMap[index_coord] + 2 * FLT_EPSILON > this_map[j];
					const bool cond3 = heightMap[index_coord] < 2 * FLT_EPSILON + this_map[j];
					const bool cond4 = prev_timestamp >= this_timestamp;
					const bool prev_is_bouyant = cond1 || (cond2 && cond3 && cond4);


					// Handle Subduction of oceanic crust as special case.
					if (this_is_oceanic && prev_is_bouyant) {
						// This plate will be the subducting one.
						// The level of effect that subduction has
						// is directly related to the amount of water
						// on top of the subducting plate.
						const float sediment = OCEANIC_BASE * (CONTINENTAL_BASE - this_map[j]) / CONTINENTAL_BASE;

						// Save collision to the receiving plate's list.
						plateCollision coll(i, x_mod, y_mod, sediment);
						subductions[ownerMap[index_coord]].push_back(coll);
						++oceanic_collisions;

						// Remove subducted oceanic Lithosphere from plate.
						// This is crucial for
						// a) having correct amount of colliding crust (below)
						// b) protecting subducted locations from receiving
						//    crust from other subductions/collisions.
						float a = this_map[j];
						plates[i].setCrust(x_mod, y_mod, this_map[j] - OCEANIC_BASE, this_timestamp);
						if (this_map[j] <= 0)
						{
							continue; // Nothing more to collide.
						}
					}
					else if (prev_is_oceanic) {
						const float sediment = OCEANIC_BASE * (CONTINENTAL_BASE - heightMap[index_coord]) / CONTINENTAL_BASE;

						plateCollision coll(ownerMap[index_coord], x_mod, y_mod, sediment);
						subductions[i].push_back(coll);
						++oceanic_collisions;

						plates[ownerMap[index_coord]].setCrust(x_mod, y_mod, heightMap[index_coord] - OCEANIC_BASE, prev_timestamp);
						heightMap[index_coord] -= OCEANIC_BASE;

						if (heightMap[index_coord] <= 0) {
							ownerMap[index_coord] = i;
							heightMap[index_coord] = this_map[j];
							ageMap[index_coord] = this_age[j];

							continue;
						}
					}
				}
				// Record collisions to both plates. This also creates
				// continent segment at the collided location to plates.
				size_t this_area = plates[i].addCollision(x_mod, y_mod);
				size_t prev_area = plates[ownerMap[index_coord]].addCollision(x_mod, y_mod);

				// At least two plates are at same location.
				// Move some crust from the SMALLER plate onto LARGER one.
				if (this_area < prev_area) {
					plateCollision coll(ownerMap[index_coord], x_mod, y_mod, this_map[j] * folding_ratio);

					// Give some...
					heightMap[index_coord] += coll.crust;
					plates[ownerMap[index_coord]].setCrust(x_mod, y_mod, heightMap[index_coord], this_age[j]);

					// And take some.
					plates[i].setCrust(x_mod, y_mod, this_map[j] * (1.0 - folding_ratio), this_age[j]);

					// Add collision to the earlier plate's list.
					collisions[i].push_back(coll);
					++continental_collisions;
				}
				else {
					plateCollision coll(i, x_mod, y_mod, heightMap[index_coord] * folding_ratio);

					plates[i].setCrust(x_mod, y_mod, this_map[j] + coll.crust, ageMap[index_coord]);

					plates[ownerMap[index_coord]].setCrust(x_mod, y_mod, heightMap[index_coord] * (1.0 - folding_ratio), ageMap[index_coord]);

					collisions[ownerMap[index_coord]].push_back(coll);
					++continental_collisions;

					// Give the location to the larger plate.
					heightMap[index_coord] = this_map[j];
					ownerMap[index_coord] = i;
					ageMap[index_coord] = this_age[j];
				}
			}
	}

	// Update the counter of iterations since last continental collision.
	if (continental_collisions == 0)
	{
		last_coll_count++;
	}

	for (size_t i = 0; i < num_plates; ++i) {
		for (size_t j = 0; j < subductions[i].size(); ++j) {
			const plateCollision& coll = subductions[i][j];


			// Do not apply friction to oceanic plates.
			// This is a very cheap way to emulate slab pull.
			// Just perform subduction and on our way we go!
			plates[i].addCrustBySubduction(
				coll.wx, coll.wy, coll.crust, currentAge,
				plates[coll.index].getVelX(),
				plates[coll.index].getVelY()
			);
		}

		subductions[i].clear();
	}

	for (size_t i = 0; i < num_plates; ++i) {
		for (size_t j = 0; j < collisions[i].size(); ++j) {
			const plateCollision& coll = collisions[i][j];
			size_t coll_count, coll_count_i, coll_count_j;
			float coll_ratio, coll_ratio_i, coll_ratio_j;

			// Collision causes friction. Apply it to both plates.
			plates[i].applyFriction(coll.crust);
			plates[coll.index].applyFriction(coll.crust);

			plates[i].getCollisionInfo(coll.wx, coll.wy, &coll_count_i, &coll_ratio_i);
			plates[coll.index].getCollisionInfo(coll.wx, coll.wy, &coll_count_j, &coll_ratio_j);

			// Find the minimum count of collisions between two
			// continents on different plates.
			// It's minimum because large plate will get collisions
			// from all over where as smaller plate will get just
			// a few. It's those few that matter between these two
			// plates, not what the big plate has with all the
			// other plates around it.
			coll_count = coll_count_i;
			if (coll_count > coll_count_j)
			{
				coll_count = coll_count_j;
			}

			// Find maximum amount of collided surface area between
			// two continents on different plates.
			// Like earlier, it's the "experience" of the smaller
			// plate that matters here.
			coll_ratio = coll_ratio_i;
			if (coll_ratio < coll_ratio_j)
			{
				coll_ratio = coll_ratio_j;
			}

			if (coll_count > aggr_overlap_abs || coll_ratio > aggr_overlap_rel) {
				float amount = plates[i].aggregateCrust(plates[coll.index], coll.wx, coll.wy);

				// Calculate new direction and speed for the
				// merged plate system, that is, for the
				// receiving plate!
				plates[coll.index].collide(plates[i], coll.wx, coll.wy, amount);
			}
		}

		collisions[i].clear();
	}

	// Fill divergent boundaries with new crustal material, molten magma.
	for (size_t y = 0, i = 0; y < BOOL_REGENERATE_CRUST * map_side; ++y)
		for (size_t x = 0; x < map_side; ++x, ++i)
			if (ownerMap[i] >= num_plates) {//
				// The owner of this new crust is that neighbour plate
				// who was located at this point before plates moved.
				ownerMap[i] = prev_ownerMap[i];


				// If this is oceanic crust then add buoyancy to it.
				// Magma that has just crystallized into oceanic crust
				// is more buoyant than that which has had a lot of
				// time to cool down and become more dense.
				ageMap[i] = currentAge;
				heightMap[i] = OCEANIC_BASE * BUOYANCY_BONUS_X;

				plates[ownerMap[i]].setCrust(x, y, OCEANIC_BASE, currentAge);
			}

	buoyancy();

	calcEnergy();
	currentAge++;

	ageMap.clear();
}

void Lithosphere::restart() throw() {
	const size_t map_area = map_side * map_side;
	ageMap.resize(map_area);

	// Update height map to include all recent changes.
	std::fill(heightMap.begin(), heightMap.end(), 0);
	for (size_t i = 0; i < num_plates; ++i) {
		const size_t x0 = (size_t)plates[i].getLeft();
		const size_t y0 = (size_t)plates[i].getTop();
		const size_t x1 = x0 + plates[i].getWidth();
		const size_t y1 = y0 + plates[i].getHeight();

		const float* this_map = plates[i].getMap();
		const std::vector<size_t> this_age = plates[i].getAge();

		// Copy first part of plate onto world map.
		for (size_t y = y0, j = 0; y < y1; ++y)
			for (size_t x = x0; x < x1; ++x, ++j) {
				const size_t x_mod = x & (map_side - 1);
				const size_t y_mod = y & (map_side - 1);

				heightMap[y_mod * map_side + x_mod] += this_map[j];
				ageMap[y_mod * map_side + x_mod] = this_age[j];
			}
	}

	// Delete plates.
	plates.clear();
}

void Lithosphere::buoyancy()
{
	const size_t map_area = map_side * map_side;
	// Add some "virginity buoyancy" to all pixels for a visual boost.
	//Show plate separation rift in ocean
	//Threadable
	for (size_t i = 0; i < (BUOYANCY_BONUS_X > 0) * map_area; ++i) {
		// Calculate the inverted age of this piece of crust.
		// Force result to be minimum between inv. age and
		// max buoyancy bonus age.
		size_t crust_age = currentAge - ageMap[i];
		crust_age = MAX_BUOYANCY_AGE - crust_age; // because unsigned does not go negative
		crust_age &= -(crust_age <= MAX_BUOYANCY_AGE); // ceil to 0 if bigger than MAX_BUOYANCY_AGE

		//only ocean
		heightMap[i] += (heightMap[i] < CONTINENTAL_BASE) * BUOYANCY_BONUS_X *
			OCEANIC_BASE * crust_age * MULINV_MAX_BUOYANCY_AGE;
	}
}

void Lithosphere::end()
{
	const size_t map_area = map_side * map_side;

	buoyancy();

	// This is the LAST cycle! Add some random noise to the map.
	//Add way to big random noise give no details to map but make all mountains bigger
	{

		auto tmp = squareDiamondAdaptater(map_side, rand(), SQRDMD_ROUGHNESS);

		float t_lowest = tmp[0], t_highest = tmp[0];
		for (size_t i = 1; i < map_area; ++i) {
			t_lowest = t_lowest < tmp[i] ? t_lowest : tmp[i];
			t_highest = t_highest > tmp[i] ? t_highest : tmp[i];
		}

		//Threadable
		for (size_t i = 0; i < map_area; ++i) {
			// Scale to range [0, 1].
			tmp[i] = ((tmp[i] - t_lowest) / (t_highest - t_lowest));

			if (heightMap[i] > CONTINENTAL_BASE)
				heightMap[i] += tmp[i] * 2;
			else
				heightMap[i] = 0.8 * heightMap[i] + 0.2 * tmp[i] * CONTINENTAL_BASE;
		}
	}

	ageMap.clear();
}

