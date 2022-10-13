#ifndef PROCESSOR_H
#define PROCESSOR_H

#ifdef __cplusplus
extern "C" {
#endif

    extern void initialize(double alpha, double beta, int sample_rate);
    extern void step(double sample, double  *position, double *velocity);
    extern void reset();
    extern void terminate();

#ifdef __cplusplus
}
#endif

#endif // PROCESSOR_H
