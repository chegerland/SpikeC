# API

## neurons.h
This header includes the definition of a neuron, utilities for it and functions which enable us to obtain a spike train from the neuron.
The central object is the `Neuron` struct, which is not general, but optimized for integrate-and-fire neurons with adaptation.

### if\_params\_t
```c
typedef struct {
  double mu;
  double D;
} if_params_t;
```
A struct that groups common parameters of an integrate-and-fire neuron, which are `mu` the mean input current and `D` the diffusion coefficient. 

### adapt\_params\_t
```c
typedef struct {
  double tau_a;
  double Delta;
} adapt_params_t;
```
A struct that groups the parameters of the adaptation variable, that follows the equation $\tau_a\dot{a} = -a + \Delta \sum \delta(t - t_i)$ where $t_i$ are the spike times of the neuron.
`tau_a` corresponds to $\tau_a$, which is the adaptation time constant and `Delta` correponds to $\Delta$ which is the kick size of the adaptation.

### Neuron
```c
typedef struct {
  enum NEURON_TYPE type;
  if_params_t *if_params;
  adapt_params_t *adapt_params;
  double (*drift)(double, int, const if_params_t *);
} Neuron;
```
A struct representing a generic integrate-and-fire neuron with or without adaptation.
The neuron has a `type`, some integrate-and-fire parameters, adaptation parameters (can be set `NULL` if adaptation is not considered) and a drift function.

### lif\_drift()
```c
double lif_drift(double v, int i, const if_params_t *params);
```
Calculates the drift of a leaky integrate-and-fire neuron, i.e. $\mu - v$.

### pif\_drift()
```c
double pif_drift(double v, int i, const if_params_t *params);
```
Calculates the drift of a perfect integrate-and-fire neuron, i.e. $\mu$.

### create\_neuron\_if()
```c
Neuron *create_neuron_if(double mu, double D, enum NEURON_TYPE type);
```
Creates a new integrate-and-fire `Neuron` from the given parameters and sets the drift function according to the given type. It also sets the adaptation to `NULL`.

### create\_neuron\_ifac()
```c
Neuron *create_neuron_ifac(double mu, double D, double tau_a, double Delta, enum NEURON_TYPE type);
```
Creates a new integrate-and-fire `Neuron` (with adaptation)  from the given parameters and sets the drift function according to the given type.

### read\_neuron()
```c
Neuron *read_neuron(ini_t *ini_file);
```
Creates a new neuron from a given ini file. See also ini file API.

::: tip usage
You can define a neuron from an ini file like so
```c
// define neuron from input file
ini_t *config = ini_load("/path/to/file.ini");
Neuron *neuron = read_neuron(config);

// do stuff with neuron

// free memory
ini_free(config);
free_neuron(neuron);
```
:::


### free\_neuron()
```c
void free_neuron(Neuron *neuron);
```
Frees memory associated with `neuron`;

### print\_neuron()
```c
void print_neuron(FILE *stream, const Neuron *neuron);
```
Prints information about the `neuron` to a stream;

::: details Example
```c
Neuron *pif = create_neuron_if(5.0, 3e-2, PIF);
print_neuron(stderr, pif);
```
This code has the following output
```bash
> ./print_test 
# [Neuron]
# type = PIF
# mu = 5.000000
# D = 0.030000
```
:::

### get\_spike\_train\_if()
```c
void get_spike_train_if(const gsl_rng *r, const Neuron *neuron,
                        const TimeFrame *time_frame, double *spike_train);
```
This routine obtaines spikes by simulating the Langevin equation of an integrate-and-fire neuron without adaptation.
It uses an Euler-Maruyama scheme to solve the stochastic differential equation.
The time step `dt` is given in the `time_frame`.
The spike train has to be the same length as the times array in `time_frame`.
When the neuron has spiked, this routine adds a `1/dt` to the according index of `spike_train`.

::: warning
This routine does not zero the `spike_train`, it only adds `1/dt` if a spike happened.
:::


### get\_spike\_train\_if\_signal()
```c
void get_spike_train_if_signal(const gsl_rng *r, const Neuron *neuron,
                               const double *signal,
                               const TimeFrame *time_frame,
                               double *spike_train);
```
Same as `get_spike_train_if()` but with an added signal.


### get\_spike\_train\_ifac()
```c
void get_spike_train_ifac(const gsl_rng *r, const Neuron *neuron,
                          const TimeFrame *time_frame, double *spike_train);
```
Same as `get_spike_train_if()` but with adaptation considered.

### get\_spike\_train\_ifac\_signal()
```c
void get_spike_train_ifac_signal(const gsl_rng *r, const Neuron *neuron,
                                 const double *signal,
                                 const TimeFrame *time_frame,
                                 double *spike_train);
```
Same as `get_spike_train_if()` but with adaptation and a signal.

## timeframe.h
This header includes the definition of a time frame as well as some utilities

### TimeFrame
```c
typedef struct {
  double t_0;
  double t_end;
  double dt;
  size_t N;
  double *t;
} TimeFrame;
```
A struct that represents a time frame with a starting time `t_0` a stop/end time `t_end` and a time step `dt`.
It also includes a pointer to an array that should contain the discretized times and `N` the size of this array.

### create\_time\_frame()
```c
TimeFrame *create_time_frame(double t_0, double t_end, double dt);
```
Creates a time frame from the given parameters. Populates the times array `t`.

### read\_time\_frame()
```c
TimeFrame *read_time_frame(ini_t *ini_file);
```
Creates a time frame from a given ini file. See also ini file API.

### free\_time\_frame()
```c
void free_time_frame(TimeFrame *time_frame);
```
Frees memory associated with the time frame.

### print\_time\_frame()
```c
void print_time_frame(FILE *stream, const TimeFrame *time_frame);
```
Prints information about the time frame to stream.

::: details Example
```c
TimeFrame *times = create_time_frame(0.0, 10.0, 1e-1);
print_time_frame(stderr, times);
```
This code has the following output
```bash
> ./print_test 
# [TimeFrame]
# t_0 = 0.000000
# t_end = 10.000000
# dt = 0.100000
```
:::
