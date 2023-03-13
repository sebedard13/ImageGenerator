
## Folders

### 1-Foundation
AKA Core Services, Base Services, Low-level Technical Services/Infrastructure
- low-level technical services, utilities, and frameworks
- data structures, threads, math, file, DB, and network I/O
### 2-Infrastructure
AKA Technical Infrastructure, High-level Technical Services
- (relatively) high-level technical services and frameworks 
- Persistence, Security

### 3-Services
AKA Low-level Business Services
- very general low-level business services used in many business domains
- CurrencyConverter

### 4-Domain
AKA Business, Application Logic, Model
- handles application layer requests
- implementation of domain rules
- domain services (POS, Inventory)
- services may be used by just one application, but there is also the possibility of multi-application services
### 5-Controller
AKA Workflow, Process, Mediation, Application
- handles presentation layer requests
- workflow
- session state
- window/page transitions
- consolidation/transformation of disparate
data for presentation
### 6-View
AKA UI, Presentation
- GUI windows
- reports
- speech interface
- HTML, XML, XSLT, JSP, Javascript, ..
### Reference

From the book Applying Uml and Patterns by Craig Larman p.203