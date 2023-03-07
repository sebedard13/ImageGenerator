
#define _USE_MATH_DEFINES

#include <cfloat> // FT_EPSILON
#include <cmath> // sin, cos
#include <cstdlib> // rand
#include <cstdio> // DEBUG print
#include <cstring> // DEBUG print

#include "Plate.h"

#include <cassert>

#define INITIAL_SPEED_X 1
#define DEFORMATION_WEIGHT 5

Plate::Plate()
{
}

Plate::Plate(Plate&& other) noexcept
	: map(std::move(other.map)),
	age(std::move(other.age)),
	width(other.width),
	height(other.height),
	world_side(other.world_side),
	mass(other.mass),
	left(other.left),
	top(other.top),
	cx(other.cx),
	cy(other.cy),
	velocity(other.velocity),
	vx(other.vx),
	vy(other.vy),
	dx(other.dx),
	dy(other.dy),
	alpha(other.alpha),
	segments(std::move(other.segments)),
	segmentMap(std::move(other.segmentMap))
{
}

Plate::Plate(const float* m, size_t w, size_t h, size_t _x, size_t _y,
             size_t plate_age, size_t _world_side) throw()
	:width(w),
	height(h),
	world_side(_world_side),
	mass(0),
	left(_x),
	top(_y),
	cx(0),
	cy(0),
	dx(0),
	dy(0) {
	const size_t A = w * h; // A as in Area.
	const double angle = 2 * M_PI * rand() / (double)RAND_MAX;
	size_t i, j, k;

	if (!m)
		return;

	map.resize(A);
	age.resize(A);
	segmentMap.resize(A);

	velocity = 1;
	alpha = -(rand() & 1) * M_PI * 0.01 * (rand() / (float)RAND_MAX);
	vx = cos(angle) * INITIAL_SPEED_X;
	vy = sin(angle) * INITIAL_SPEED_X;

	std::fill(segmentMap.begin(), segmentMap.end(), 255);

	for (j = k = 0; j < height; ++j)
		for (i = 0; i < width; ++i, ++k) {
			// Clone map data and count crust mass.
			mass += map[k] = m[k];

			// Calculate center coordinates weighted by mass.
			cx += i * m[k];
			cy += j * m[k];

			// Set the age of ALL points in this plate to same
			// value. The right thing to do would be to simulate
			// the generation of new oceanic crust as if the plate
			// had been moving to its current direction until all
			// plate's (oceanic) crust receive an age.
			if (m[k] > 0)
			{
				age[k] = plate_age;
			}
			else
			{
				age[k] = 0;
			}
		}

	// Normalize center of mass coordinates.
	cx /= mass;
	cy /= mass;
}

Plate::~Plate() throw() {

}

size_t Plate::addCollision(size_t wx, size_t wy) throw() {
	size_t lx = wx, ly = wy;
	auto mapIndex = getMapIndex(lx, ly);
	size_t index = mapIndex.first;
	if (index < width * height)//check out of plate
	{
		lx = mapIndex.second.first;
		ly = mapIndex.second.second;
	}

	size_t seg = segmentMap[index];

	if (seg >= segments.size())
		seg = createSegment(lx, ly);


	segments[seg].coll_count++;
	return segments[seg].area;
}

void Plate::addCrustByCollision(size_t x, size_t y, float mapHeight, size_t age, size_t activeContinent) throw() {
	// Add crust. Extend plate if necessary.
	setCrust(x, y, getCrust(x, y) + mapHeight, age);

	auto mapIndex = getMapIndex(x, y);
	size_t index = mapIndex.first;
	if (index < width * height)//check out of plate
	{
		x = mapIndex.second.first;
		y = mapIndex.second.second;
	}


	//update segement to reflate the new addition
	segmentMap[index] = activeContinent;
	segmentData& data = segments[activeContinent];

	++data.area;
	if (y < data.y0) data.y0 = y;
	if (y > data.y1) data.y1 = y;
	if (x < data.x0) data.x0 = x;
	if (x > data.x1) data.x1 = x;
}

void Plate::addCrustBySubduction(size_t x, size_t y, float z, size_t t,
                                 float dx, float dy) throw() {
	auto mapIndex = getMapIndex(x, y);
	size_t index = mapIndex.first;
	if (index < width * height)//check out of plate
	{
		x = mapIndex.second.first;
		y = mapIndex.second.second;
	}

	// Take vector difference only between plates that move more or less
	// to same direction. This makes subduction direction behave better
	float dot = vx * dx + vy * dy;
	if (dot > 0)
	{
		dx -= vx;
		dy -= vy;
	}


	float offset = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);

	int d = (2 * (rand() % 2) - 1);
	offset *= offset * offset * d;
	dx = 10 * dx + 3 * offset;
	dy = 10 * dx + 3 * offset;

	size_t x2 = static_cast<size_t>(static_cast<int>(x) + dx);
	size_t y2 = static_cast<size_t>(static_cast<int>(y) + dy);


	//the plate is continuous only if the size equals world_side
	// if not we are probably out of plate
	if (width == world_side)
	{
		x2 = x2 % width;
	}
	if (height == world_side)
	{
		y2 = y2 % height;
	}

	index = y2 * width + x2;

	if (index < width * height && map[index] > 0) {
		t = (age[index] + t) / 2;
		age[index] = t * (z > 0);

		map[index] += z;
		mass += z;
	}
}

float Plate::aggregateCrust(Plate& p, size_t wx, size_t wy) throw() {
	size_t lx = wx, ly = wy;
	auto mapIndex = getMapIndex(lx, ly);
	const size_t index = mapIndex.first;
	if (index < width * height)//out of plate
	{
		lx = mapIndex.second.first;
		ly = mapIndex.second.second;
	}


	const size_t seg_id = segmentMap[index];

	// This check forces the caller to do things in proper order!
	//
	// Usually continents collide at several locations simultaneously.
	// Thus if this segment that is being merged now is removed from
	// segmentation bookkeeping, then the next point of collision that is
	// processed during the same iteration step would cause the test
	// below to be true and system would experience a premature abort.
	//
	// Therefore, segmentation bookkeeping is left intact. It doesn't
	// cause significant problems because all crust is cleared and empty
	// points are not processed at all.


	// One continent may have many points of collision. If one of them
	// causes continent to aggregate then all successive collisions and
	// attempts of aggregation would necessarily change nothing at all,
	// because the continent was removed from this plate earlier!
	if (segments[seg_id].area == 0)
		return 0;    // Do not process empty continents.

	size_t activeContinent = p.selectCollisionSegment(wx, wy);

	// Wrap coordinates around world edges to safeguard subtractions.
	wx += world_side;
	wy += world_side;

	float old_mass = mass;

	// Add all of the collided continent's crust to destination plate.
	for (size_t y = segments[seg_id].y0; y <= segments[seg_id].y1; ++y)
		for (size_t x = segments[seg_id].x0; x <= segments[seg_id].x1; ++x) {
			const size_t i = y * width + x;
			if (segmentMap[i] == seg_id && map[i] > 0) {
				p.addCrustByCollision(wx + x - lx, wy + y - ly, map[i], age[i], activeContinent);

				mass -= map[i];
				map[i] = 0;
			}
		}

	segments[seg_id].area = 0; // Mark segment as non-exitent.
	return old_mass - mass;
}

void Plate::applyFriction(float deformed_mass) throw() {
	// Remove the energy that deformation consumed from plate's kinetic
	// energy: F - dF = ma - dF => a = dF/m.
	if (mass > 0) {
		float vel_dec = DEFORMATION_WEIGHT * deformed_mass / mass;

		if (vel_dec < velocity)
			// Altering the source variable causes the order of calls to
			// this function to have difference when it shouldn't!
			// However, it's a hack well worth the outcome. :)
			//what?
			velocity -= vel_dec;
		else
			velocity = 0;
	}
}

void Plate::collide(Plate& p, size_t wx, size_t wy, float coll_mass) throw() {
	const float coeff_rest = 0.0; // Coefficient of restitution.
	// 1 = fully elastic, 0 = stick together.

// Calculate the normal to the curve/line at collision point.
// The normal will point into plate B i.e. the "other" plate.
//
// Plates that wrap over world edges can mess the normal vector.
// This could be solved by choosing the normal vector that points the
// shortest path beween mass centers but this causes problems when
// plates are like heavy metal balls at a long rod and one plate's ball
// collides at the further end of other plate's rod. Sure, this is
// nearly never occurring situation but if we can easily do better then
// why not do it?
//
// Better way is to select that normal vector that points along the
// line that passes nearest the point of collision. Because point's
// distance from line segment is relatively cumbersome to perform, the
// vector is constructed as the sum of vectors <massCenterA, P> and
// <P, massCenterB>. This solution works because collisions always
// happen in the overlapping region of the two plates.
	size_t apx = wx, apy = wy, bpx = wx, bpy = wy;
	float ap_dx, ap_dy, bp_dx, bp_dy, nx, ny;
	auto mapIndexA = getMapIndex(apx, apy);
	size_t index = mapIndexA.first;
	if (index < width * height)//out of plate
	{
		apx = mapIndexA.second.first;
		apy = mapIndexA.second.second;
	}


	auto mapIndexB = p.getMapIndex(bpx, bpy);
	size_t p_index = mapIndexB.first;
	if (p_index < p.width * p.height)//out of plate
	{
		bpx = mapIndexB.second.first;
		bpy = mapIndexB.second.second;
	}



	ap_dx = (int)apx - (int)cx;
	ap_dy = (int)apy - (int)cy;
	bp_dx = (int)bpx - (int)p.cx;
	bp_dy = (int)bpy - (int)p.cy;
	nx = ap_dx - bp_dx;
	ny = ap_dy - bp_dy;

	if (nx * nx + ny * ny <= 0)
		return; // Avoid division by zero!

	// Scaling is required at last when impulses are added to plates!
	float n_len = sqrt(nx * nx + ny * ny);
	nx /= n_len;
	ny /= n_len;

	// Compute relative velocity between plates at the collision point.
	// Because torque is not included, calc simplifies to v_ab = v_a - v_b.
	const float rel_vx = vx - p.vx;
	const float rel_vy = vy - p.vy;

	// Get the dot product of relative velocity vector and collision vector.
	// Then get the projection of v_ab along collision vector.
	// Note that vector n must be a unit vector!
	const float rel_dot_n = rel_vx * nx + rel_vy * ny;

	if (rel_dot_n <= 0) {
		return; // Exit if objects are moving away from each other.
	}

	// Calculate the denominator of impulse: n . n * (1 / m_1 + 1 / m_2).
	// Use the mass of the colliding crust for the "donator" plate.
	float denom = (nx * nx + ny * ny) * (1.0 / mass + 1.0 / coll_mass);

	// Calculate force of impulse.
	float J = -(1 + coeff_rest) * rel_dot_n / denom;

	// Compute final change of trajectory.
	// The plate that is the "giver" of the impulse should receive a
	// force according to its pre-collision mass, not the current mass!
	dx += nx * J / mass;
	dy += ny * J / mass;
	p.dx -= nx * J / (coll_mass + p.mass);
	p.dy -= ny * J / (coll_mass + p.mass);

	// In order to prove that the code above works correctly, here is an
	// example calculation with ball A (mass 10) moving right at velocity
	// 1 and ball B (mass 100) moving up at velocity 1. Collision point
	// is at rightmost point of ball A and leftmost point of ball B.
	// Radius of both balls is 2.
	// ap_dx =  2;
	// ap_dy =  0;
	// bp_dx = -2;
	// bp_dy =  0;
	// nx = 2 - -2 = 4;
	// ny = 0 -  0 = 0;
	// n_len = sqrt(4 * 4 + 0) = 4;
	// nx = 4 / 4 = 1;
	// ny = 0 / 4 = 0;
	//
	// So far so good, right? Normal points into ball B like it should.
	//
	// rel_vx = 1 -  0 = 1;
	// rel_vy = 0 - -1 = 1;
	// rel_dot_n = 1 * 1 + 1 * 0 = 1;
	// denom = (1 * 1 + 0 * 0) * (1/10 + 1/100) = 1 * 11/100 = 11/100;
	// J = -(1 + 0) * 1 / (11/100) = -100/11;
	// dx = 1 * (-100/11) / 10 = -10/11;
	// dy = 0;
	// p.dx = -1 * (-100/11) / 100 = 1/11;
	// p.dy = -0;
	//
	// So finally:
	// vx = 1 - 10/11 = 1/11
	// vy = 0
	// p.vx = 0 + 1/11 = 1/11
	// p.vy = -1
	//
	// We see that in with restitution 0, both balls continue at same
	// speed along X axis. However at the same time ball B continues its
	// path upwards like it should. Seems correct right?
}

void Plate::erode(float lower_bound) throw() {
	std::vector<float>tmp(width * height);


	mass = 0;
	cx = cy = 0;

	for (size_t y = 0; y < height; ++y)
		for (size_t x = 0; x < width; ++x) {
			const size_t index = y * width + x;
			mass += map[index];
			tmp[index] += map[index]; // Careful not to overwrite earlier amounts.

			// Update the center coordinates weighted by mass.
			cx += x * map[index];
			cy += y * map[index];

			if (map[index] < lower_bound)
				continue;

			// Calculate the x and y offset of neighbour directions.
			// If neighbour is out of plate edges, set it to zero. This protects
			// map memory reads from segment faulting.
			// Calculate offsets within map memory.
			size_t w = (x - 1 + width);
			w = w % width;
			w = y * width + w;

			size_t e = (x + 1);
			e = e % width;
			e = y * width + e;

			size_t n = (y - 1 + height);
			n = n % height;
			n = n * width + x;

			size_t s = (y + 1);
			s = s % height;
			s = s * width + x;

			// Extract neighbours heights. Apply validity filtering: 0 is invalid.
			float w_crust = 0;
			if (map[w] < map[index])
			{
				w_crust = map[w];
			}
			float e_crust = 0;
			if (map[e] < map[index])
			{
				e_crust = map[e];
			}
			float n_crust = 0;
			if (map[n] < map[index])
			{
				n_crust = map[n];
			}
			float s_crust = 0;
			if (map[s] < map[index])
			{
				s_crust = map[s];
			}

			// Ither this location has no neighbours (ARTIFACT!) or it is the
			// lowest part of its area. In either case the work here is done.
			if (w_crust + e_crust + n_crust + s_crust == 0)
				continue;

			// Calculate the difference in height between this point and its
			// nbours that are lower than this point.
			float w_diff = map[index] - w_crust;
			float e_diff = map[index] - e_crust;
			float n_diff = map[index] - n_crust;
			float s_diff = map[index] - s_crust;

			float min_diff = w_diff;
			min_diff -= (min_diff - e_diff) * (e_diff < min_diff);
			min_diff -= (min_diff - n_diff) * (n_diff < min_diff);
			min_diff -= (min_diff - s_diff) * (s_diff < min_diff);

			// Calculate the sum of difference between lower neighbours and
			// the TALLEST lower neighbour.
			float diff_sum = (w_diff - min_diff) * (w_crust > 0) +
				(e_diff - min_diff) * (e_crust > 0) +
				(n_diff - min_diff) * (n_crust > 0) +
				(s_diff - min_diff) * (s_crust > 0);

			if (diff_sum < min_diff) {
				// There's NOT enough room in neighbours to contain all the
				// crust from this peak so that it would be as tall as its
				// tallest lower neighbour. Thus first step is make ALL
				// lower neighbours and this point equally tall.
				tmp[w] += (w_diff - min_diff) * (w_crust > 0);
				tmp[e] += (e_diff - min_diff) * (e_crust > 0);
				tmp[n] += (n_diff - min_diff) * (n_crust > 0);
				tmp[s] += (s_diff - min_diff) * (s_crust > 0);
				tmp[index] -= min_diff;

				min_diff -= diff_sum;

				// Spread the remaining crust equally among all lower nbours.
				min_diff /= 1 + (w_crust > 0) + (e_crust > 0) +
					(n_crust > 0) + (s_crust > 0);

				tmp[w] += min_diff * (w_crust > 0);
				tmp[e] += min_diff * (e_crust > 0);
				tmp[n] += min_diff * (n_crust > 0);
				tmp[s] += min_diff * (s_crust > 0);
				tmp[index] += min_diff;
			}
			else {
				float unit = min_diff / diff_sum;

				// Remove all crust from this location making it as tall as
				// its tallest lower neighbour.
				tmp[index] -= min_diff;

				// Spread all removed crust among all other lower neighbours.
				tmp[w] += unit * (w_diff - min_diff) * (w_crust > 0);
				tmp[e] += unit * (e_diff - min_diff) * (e_crust > 0);
				tmp[n] += unit * (n_diff - min_diff) * (n_crust > 0);
				tmp[s] += unit * (s_diff - min_diff) * (s_crust > 0);
			}
		}

	map = std::move(tmp);

	if (mass > 0) {
		cx /= mass;
		cy /= mass;
	}
}

void Plate::getCollisionInfo(size_t wx, size_t wy, size_t* count,
                             float* ratio) const throw() {
	size_t lx = wx, ly = wy;
	size_t index = getMapIndex(lx, ly).first;
	size_t seg = segments.size();

	*count = 0;
	*ratio = 0;

	seg = segmentMap[index];

	*count = segments[seg].coll_count;
	*ratio = (float)segments[seg].coll_count /
		(float)(1 + segments[seg].area); // +1 avoids DIV with zero.
}

size_t Plate::getContinentArea(size_t wx, size_t wy) const throw() {
	const size_t index = getMapIndex(wx, wy).first;

	return segments[segmentMap[index]].area;
}

float Plate::getCrust(size_t x, size_t y) const throw() {
	const size_t index = getMapIndex(x, y).first;
	return index < (size_t)(-1) ? map[index] : 0;
}

size_t Plate::getCrustTimestamp(size_t x, size_t y) const throw() {
	const size_t index = getMapIndex(x, y).first;
	return index < (size_t)(-1) ? age[index] : 0;
}

const std::vector<size_t>& Plate::getAge()
{
	return  age;
}

const float* Plate::getMap()
{
	return map.data();
}

void Plate::move() throw() {
	// Apply any new impulses to the plate's trajectory.
	vx += dx;
	vy += dy;
	dx = 0;
	dy = 0;

	// Force direction of plate to be unit vector.
	// Update velocity so that the distance of movement doesn't change.
	const float vNorm = sqrt(vx * vx + vy * vy);
	vx /= vNorm;
	vy /= vNorm;
	velocity += vNorm - 1.0;//what

	// velocity * 1 or *0 for 
	velocity *= velocity > 0; // Round negative values to zero.


	// Location modulations into range [0, world_side[ are a have to!
	// If left undone SOMETHING WILL BREAK DOWN SOMEWHERE in the code!

	left += vx * velocity;

	if (left < 0)
		left += world_side;
	else if (left >= world_side)
		left -= world_side;

	top += vy * velocity;

	if (top < 0)
		top += world_side;
	else if (top >= world_side)
		top -= world_side;
}

void Plate::resetSegments() throw() {
	std::fill(segmentMap.begin(), segmentMap.end(), -1);
	segments.clear();
}

unsigned roundUp(unsigned numToRound, const unsigned multiple)
{
	assert(multiple % 2 == 0);
	return (numToRound + multiple - 1) & -multiple;
}

template <typename T> int sign(T val) {
	return (T(0) < val) - (val < T(0));
}

void Plate::setCrust(size_t x, size_t y, float newMass, size_t ageOfNewCrust) throw() {
	if (newMass < 0) // Do not accept negative values.
		newMass = 0;

	size_t _x = x;
	size_t _y = y;
	auto mapIndex = getMapIndex(_x, _y);
	size_t index = mapIndex.first;

	auto coord = mapIndex.second;

	//grow crust
	if (index >= width * height) {
		std::pair<int, int> diff{ 0,0 };

		// smallest deplacement or grow because move in negative (could be changed)
		//if (coord.first < width) // better way
		if (coord.first - width <= world_side - coord.first || (world_side - coord.first) > left) {
			//Grow width
			diff.first = coord.first - width + 1;
			if (diff.first < 0) { diff.first = 0; }
		}
		else {
			//Move left
			diff.first = coord.first - world_side;
			// we don't check if inside and grow because the coord is inside an axe
		}
		//}


		//if (coord.second >= height) { // better way
		if (coord.second - height <= world_side - coord.second || (world_side - coord.second) > top) {
			diff.second = coord.second - height + 1;
			if (diff.second < 0) { diff.second = 0; }
		}
		else {
			diff.second = coord.second - world_side;
			// we don't check if inside and grow because the coord is inside an axe
		}
		//}

		// Scale all changes to multiple of 8.
		diff.first = sign(diff.first) * roundUp(std::abs(diff.first) + 1, 8);
		diff.second = sign(diff.second) * roundUp(std::abs(diff.second) + 1, 8);


		// Make sure plate doesn't grow bigger than the system it's in!
		if (width + std::abs(diff.first) > world_side)
		{
			diff.first = world_side - width;
		}

		if (height + std::abs(diff.second) > world_side)
		{
			diff.second = world_side - height;
		}

		const size_t oldWidth = width;
		const size_t oldHeight = height;

		size_t diffLeft = 0;
		size_t diffTop = 0;

		if (diff.first < 0)
		{
			left += diff.first;
			diffLeft = -diff.first;
		}
		width += std::abs(diff.first);

		if (diff.second < 0)
		{
			top += diff.second;
			diffTop = -diff.second;
		}
		height += std::abs(diff.second);

		std::vector<float> tmph(width * height);
		std::vector<size_t> tmpa(width * height);
		std::vector<size_t> tmps(width * height);

		std::fill(tmpa.begin(), tmpa.end(), 0);
		std::fill(tmps.begin(), tmps.end(), 255);

		// copy old plate into new.
		for (size_t y = 0; y < oldHeight; ++y) {
			for (int x = 0; x < oldWidth; ++x)
			{
				const size_t dest_i = (diffTop + y) * width + diffLeft + x;
				const size_t src_i = y * oldWidth + x;

				tmph[dest_i] = map[src_i];
				tmpa[dest_i] = age[src_i];
				tmps[dest_i] = segmentMap[src_i];
			}
		}

		age.clear();
		segmentMap.clear();
		map = std::move(tmph);
		age = std::move(tmpa);
		segmentMap = std::move(tmps);

		// Shift all segment data to match new coordinates.
		for (size_t s = 0; s < segments.size(); ++s) {
			segments[s].x0 += diffLeft;
			segments[s].x1 += diffLeft;
			segments[s].y0 += diffTop;
			segments[s].y1 += diffTop;
		}

		_x = x, _y = y;
		index = getMapIndex(_x, _y).first;
	}


	// Update crust's age.
	// If old crust exists, new age is mean of original and supplied ages.
	// If no new crust is added, original time remains intact.
	size_t age2 = ageOfNewCrust;
	if (map[index] > 0)
	{
		age2 = (age2 + age[index]) / 2;
	}
	age[index] = age2;

	//remove old mass and replace
	mass -= map[index];
	map[index] = newMass;        // Set new crust height to desired location.
	mass += newMass;        // Update mass counter.
}

unsigned Plate::selectCollisionSegment(size_t coll_x, size_t coll_y) throw() {
	size_t index = getMapIndex(coll_x, coll_y).first;
	return segmentMap[index];

}

///////////////////////////////////////////////////////////////////////////////
/// Private methods ///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

size_t Plate::createSegment(size_t x, size_t y) throw() {
	const size_t origin_index = y * width + x;
	const size_t ID = segments.size();

	if (segmentMap[origin_index] < ID)
		return segmentMap[origin_index];


	//next to position
	size_t goUp = (y - 1 + height) % (height)*width + x;
	size_t goDown = (y + 1) % (height)*width + x;
	size_t goLeft = y * width + (x - 1 + width) % (width);
	size_t goRight = y * width + (x + 1) % (width);
	size_t nbour_id = ID;

	if (map[goLeft] >= CONT_BASE && segmentMap[goLeft] < nbour_id)
	{
		nbour_id = segmentMap[goLeft];
	}
	else if (map[goRight] >= CONT_BASE && segmentMap[goRight] < nbour_id)
	{
		if (x + 1 != world_side) //bug?
		{
			nbour_id = segmentMap[goRight];
		}
	}
	else if (map[goUp] >= CONT_BASE && segmentMap[goUp] < nbour_id)
	{
		nbour_id = segmentMap[goUp];
	}
	else if (map[goDown] >= CONT_BASE && segmentMap[goDown] < nbour_id)
	{
		if (y + 1 != world_side) //bug?
		{
			nbour_id = segmentMap[goDown];
		}
	}

	if (nbour_id < ID) {
		segmentMap[origin_index] = nbour_id;
		++segments[nbour_id].area;

		if (y < segments[nbour_id].y0) segments[nbour_id].y0 = y;
		else if (y > segments[nbour_id].y1) segments[nbour_id].y1 = y;
		if (x < segments[nbour_id].x0) segments[nbour_id].x0 = x;
		else if (x > segments[nbour_id].x1) segments[nbour_id].x1 = x;

		return nbour_id;
	}

	segmentData data(x, y, x, y, 0);
	std::vector<std::pair<size_t, size_t>> spans_todo2{};
	spans_todo2.reserve(height);
	spans_todo2.emplace_back(x, y);
	bool first = true;
	while (!spans_todo2.empty())
	{
		auto current = spans_todo2.back();

		spans_todo2.pop_back();
		size_t cu_x = current.first;
		size_t cu_y = current.second;
		size_t coordIndex = cu_y * width + cu_x;

		if ((map[coordIndex] >= CONT_BASE && segmentMap[coordIndex] > ID) || first)
		{
			//change data
			segmentMap[coordIndex] = ID;
			first = false;

			data.area++;
			if (cu_y < data.y0) data.y0 = cu_y;
			else if (cu_y > data.y1) data.y1 = cu_y;
			if (cu_x < data.x0) data.x0 = cu_x;
			else if (cu_x > data.x1) data.x1 = cu_x;

			//find next coord
			spans_todo2.emplace_back(cu_x, (cu_y - 1 + height) % (height));//up
			spans_todo2.emplace_back(cu_x, (cu_y + 1) % (height));//down
			spans_todo2.emplace_back((cu_x - 1 + width) % width, cu_y);//left
			spans_todo2.emplace_back((cu_x + 1) % width, cu_y);//right
		}
	}

	segments.push_back(data);
	return ID;
}

std::pair<size_t, std::pair<size_t, size_t>> Plate::getMapIndex(const size_t px, const size_t py) const throw() {
	const auto uLeft = (unsigned)left;
	const auto uTop = (unsigned)top;
	size_t x, y;
	size_t px2, py2;

	px2 = px % world_side;
	py2 = py % world_side;
	if (px2 < uLeft)
	{
		size_t tmp = world_side - uLeft;
		x = tmp + px2;
	}
	else
	{
		x = px2 - uLeft;
	}


	if (py2 < uTop)
	{
		size_t tmp = world_side - uTop;
		y = tmp + py2;
	}
	else
	{
		y = py2 - uTop;
	}
	if (x >= width || y >= height)
	{
		return { static_cast<size_t>(-1), { x,y } };
	}

	return { y * width + x, { x,y } };
}


