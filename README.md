# Philosophers

A multithreaded C implementation of the classic [Dining Philosophers Problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem) using POSIX threads and mutexes.

## 📖 About

The Dining Philosophers Problem is a classic synchronization problem in computer science that illustrates the challenges of avoiding deadlock and resource contention in concurrent programming. This implementation simulates philosophers sitting around a circular table, each needing two forks to eat, with the goal of preventing starvation and deadlock.

### The Problem

- N philosophers sit around a circular table
- Each philosopher alternates between thinking, eating, and sleeping
- There are N forks (one between each pair of adjacent philosophers)
- A philosopher needs both adjacent forks to eat
- Philosophers cannot communicate with each other
- The challenge is to design an algorithm that prevents deadlock and starvation

## 🚀 Features

- **Thread-based simulation**: Each philosopher runs in its own thread
- **Deadlock prevention**: Careful fork acquisition strategy prevents deadlocks
- **Starvation monitoring**: Tracks when each philosopher last ate to prevent starvation
- **Configurable parameters**: Customizable timing and philosopher count
- **Real-time logging**: Timestamped output of all philosopher actions
- **Graceful termination**: Clean exit when simulation conditions are met

## 🔧 Building

### Prerequisites

- GCC compiler
- POSIX-compliant system (Linux, macOS, Unix)
- Make

### Compilation

```bash
cd philo
make
```

This will create the `philo` executable in the `philo` directory.

### Cleaning

```bash
make clean    # Remove object files
make fclean   # Remove object files and executable
make re       # Clean and rebuild
```

## 💻 Usage

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

### Arguments

| Argument | Type | Description |
|----------|------|-------------|
| `number_of_philosophers` | int > 0 | Number of philosophers (and forks) around the table |
| `time_to_die` | int > 0 | Time in milliseconds after which a philosopher dies if they haven't started eating |
| `time_to_eat` | int > 0 | Time in milliseconds it takes for a philosopher to eat |
| `time_to_sleep` | int > 0 | Time in milliseconds a philosopher spends sleeping |
| `number_of_times_each_philosopher_must_eat` | int > 0 (optional) | Simulation stops when all philosophers have eaten at least this many times |

### Example Usage

```bash
# 5 philosophers, die after 800ms, eat for 200ms, sleep for 200ms
./philo 5 800 200 200

# Same as above, but stop when each philosopher has eaten 7 times
./philo 5 800 200 200 7

# Edge case: single philosopher (will starve)
./philo 1 800 200 200

# Large table
./philo 20 410 200 200
```

## 📋 Output Format

The program outputs timestamped messages for each philosopher action:

```
timestamp_in_ms philosopher_id action
```

### Possible Actions

- `has taken a fork`
- `is eating`
- `is sleeping` 
- `is thinking`
- `died`

### Example Output

```
0 1 has taken a fork
0 1 has taken a fork
0 1 is eating
200 1 is sleeping
400 1 is thinking
```

## 🏗️ Implementation Details

### Architecture

The program uses a multi-threaded approach where:

- **Main thread**: Initializes the simulation, creates philosopher threads, and monitors the simulation
- **Philosopher threads**: Each philosopher runs independently, following the eat-sleep-think cycle
- **Shared resources**: Forks are represented as mutexes, shared between adjacent philosophers

### Key Components

#### Data Structures

```c
typedef struct s_philo {
    t_program       *program;        // Reference to main program
    pthread_mutex_t *l_fork;         // Left fork (mutex)
    pthread_mutex_t *r_fork;         // Right fork (mutex)
    size_t          last_eat;        // Timestamp of last meal
    int             no_eaten;        // Number of meals eaten
    int             id;              // Philosopher ID
    pthread_t       t;               // Thread handle
} t_philo;

typedef struct s_program {
    int             no_philos;       // Number of philosophers
    t_philo         *philos;         // Array of philosophers
    pthread_mutex_t lock;            // Main synchronization lock
    pthread_mutex_t *forks;          // Array of fork mutexes
    size_t          eat_time;        // Time to eat (ms)
    size_t          die_time;        // Time until death (ms)
    size_t          sleep_time;      // Time to sleep (ms)
    size_t          start_time;      // Simulation start time
    int             no_full;         // Number of satisfied philosophers
    int             no_meals;        // Required meals per philosopher
    int             stop;            // Stop flag
    int             start;           // Start flag
} t_program;
```

#### Synchronization Strategy

- **Fork acquisition**: Philosophers acquire forks in a consistent order to prevent deadlock
- **Global lock**: Used for synchronized printing and shared state updates
- **Death monitoring**: Main thread continuously checks if any philosopher has starved
- **Completion detection**: Simulation ends when all philosophers have eaten enough meals (if specified)

### Thread Safety

- All shared data access is protected by mutexes
- Fork mutexes prevent multiple philosophers from using the same fork
- Global program lock ensures atomic updates to shared state
- Careful timing and state checking prevents race conditions

## 🎯 42 School Project

This project is part of the 42 School curriculum and focuses on:

- **Threading concepts**: Creating and managing multiple threads
- **Mutex usage**: Preventing race conditions and ensuring thread safety
- **Deadlock prevention**: Implementing strategies to avoid deadlocks
- **Resource management**: Proper allocation and cleanup of system resources
- **Algorithm design**: Solving classic computer science problems

## ⚠️ Important Notes

- The simulation uses busy-waiting with `usleep()` for timing precision
- All times are specified in milliseconds
- Philosophers are numbered starting from 1
- The program will run indefinitely unless:
  - A philosopher dies (starvation)
  - All philosophers reach the meal count (if specified)
- Memory and thread cleanup is handled automatically on exit

## 🧠 Algorithm Insights

This implementation addresses several key challenges:

1. **Deadlock Prevention**: Careful fork acquisition order prevents circular waiting
2. **Starvation Prevention**: Continuous monitoring ensures no philosopher starves
3. **Fairness**: All philosophers get equal opportunity to eat
4. **Performance**: Efficient synchronization minimizes overhead

The solution demonstrates practical application of operating system concepts including mutual exclusion, critical sections, and concurrent programming patterns.
