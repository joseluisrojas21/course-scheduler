# Course Scheduler

The Course Scheduler is a command-line tool that helps students generate and filter possible course schedules from a CSV file containing course information. Users can view schedules based on specific criteria such as time ranges, days, and CRNs.

## Features
- View all possible schedules.
- Filter schedules by:
    - Time range
    - Specific days
    - Number of CRNs
    - Combination of time range, days, and CRNs
- Save generated schedules based on selected criteria.

## Installation
### 1. Clone the Repository

```bash
git clone https://github.com/joseluisrojas21/course-scheduler.git
cd course-scheduler
```

### 2. Build it with make
```
make
```

### 3. Run the program
```
./scheduler
```

#### Run with debug options
- 1: Debug course combination generation
- 2: Debug position queue size
- 3: Debug time and date comparison

```
./scheduler -d option
```

### Usage
Follow the prompts to input your filtering criteria and view the resulting schedules.
```
1. View all possible schedules
2. View schedules within a specific time range
3. View schedules within a specific time range on selected days
4. View schedules containing a specific number of CRNs
5. View schedules within a specific time range, containing a specific number of CRNs, on selected days
6. Go back
7. Exit
```

### CSV file
| CRN | Course | Section Number | Credit Hours |             Title           | Days |     Time    | Workshop | Instructor |   Building  |
|-----|--------|----------------|--------------|-----------------------------|------|-------------|----------|------------|-------------|
|11889|  CS    |      2302      |      3       |       Data Structures       | M W  |12:00 - 13:20|          | Instructor | CCSB G.0208 |
|16022|  CS    |      2302      |      3       |       Data Structures       | M W  |13:30 - 14:50|          | Instructor | CCSB 1.0202 |
|18421|  CS    |      2302      |      3       |       Data Structures       | T R  |13:30 - 14:50|          | Instructor | CCSB 1.0202 |
|10898|  ASTR  |      1307      |      3       | Elem Astronomy-Solar System | T R  |13:30 - 14:50|          | Instructor | Union Cinema|
|13598|  ASTR  |      1307      |      3       | Elem Astronomy-Solar System | M W  |9:00  - 10:20|          | Instructor | PSCI 115    |
|17912|  ASTR  |      1107      |      1       | Astronomy Lab I             | W    |14:00 - 15:50|          | Instructor | PSCI 321    |
|10929|  ASTR  |      1107      |      1       | Astronomy Lab I             | T    |10:30 - 12:20|          | Instructor | PSCI 321    |
|10931|  ASTR  |      1107      |      1       | Astronomy Lab I             | M    |12:00 - 13:50|          | Instructor | PSCI 321    |

### Combinations
| Combination # |  CS   | ASTR  | ASTR Lab |
|---------------|-------|-------|----------|
|**1**          | 11889 | 10898 |  17912   |
|**2**          | 11889 | 10898 |  10929   |
|3              | 11889 | 10898 |  10931   |
|**4**          | 11889 | 13598 |  17912   |
|**5**          | 11889 | 13598 |  10929   |
|6              | 11889 | 13598 |  10931   |
|7              | 16022 | 10898 |  17912   |
|**8**          | 16022 | 10898 |  10929   |
|9              | 16022 | 10898 |  10931   |
|10             | 16022 | 13598 |  17912   |
|**11**         | 16022 | 13598 |  10929   |
|12             | 16022 | 13598 |  10931   |
|13             | 18421 | 10898 |  17912   |
|14             | 18421 | 10898 |  10929   |
|15             | 18421 | 10898 |  10931   |
|**16**         | 18421 | 13598 |  17912   |
|**17**         | 18421 | 13598 |  10929   |
|**18**         | 18421 | 13598 |  10931   |

### Valid schedules
|Combination #|CRN  |Title                      |Days|Time           |
|-------------|-----|---------------------------|----|---------------|
|1            |17912|Astronomy Lab I            |W   |14:00  -  15:50|
|             |11889|Data Structures            |M W |12:00  -  13:20|
|             |10898|Elem Astronomy-Solar System|T R |13:30  -  14:50|
|2            |10929|Astronomy Lab I            |T   |10:30  -  12:20|
|             |11889|Data Structures            |M W |12:00  -  13:20|
|             |10898|Elem Astronomy-Solar System|T R |13:30  -  14:50|
|4            |17912|Astronomy Lab I            |W   |14:00  -  15:50|
|             |11889|Data Structures            |M W |12:00  -  13:20|
|             |13598|Elem Astronomy-Solar System|M W | 9:00  -  10:20|
|5            |10929|Astronomy Lab I            |T   |10:30  -  12:20|
|             |11889|Data Structures            |M W |12:00  -  13:20|
|             |13598|Elem Astronomy-Solar System|M W | 9:00  -  10:20|
|8            |10929|Astronomy Lab I            |T   |10:30  -  12:20|
|             |16022|Data Structures            |M W |13:30  -  14:50|
|             |10898|Elem Astronomy-Solar System|T R |13:30  -  14:50|
|11           |10929|Astronomy Lab I            |T   |10:30  -  12:20|
|             |16022|Data Structures            |M W |13:30  -  14:50|
|             |13598|Elem Astronomy-Solar System|M W | 9:00  -  10:20|
|16           |17912|Astronomy Lab I            |W   |14:00  -  15:50|
|             |18421|Data Structures            |T R |13:30  -  14:50|
|             |13598|Elem Astronomy-Solar System|M W | 9:00  -  10:20|
|17           |10929|Astronomy Lab I            |T   |10:30  -  12:20|
|             |18421|Data Structures            |T R |13:30  -  14:50|
|             |13598|Elem Astronomy-Solar System|M W | 9:00  -  10:20|
|18           |10931|Astronomy Lab I            |M   |12:00  -  13:50|
|             |18421|Data Structures            |T R |13:30  -  14:50|
|             |13598|Elem Astronomy-Solar System|M W | 9:00  -  10:20|