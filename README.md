# OORA
For classes on code optymization

## Usage

$ mkdir build

$ cd mkdir

$ cmake -DPAPI_PREFIX=\<path to PAPI\> ..

$ make


For example

$ cmake -DPAPI_PREFIX=/opt/papi ..

# PAPI

To use PAPI_flops you need to have floating point operations event supported by the platform.

The first call to PAPI_flops initializes the PAPI library, set up the counters to monitor PAPI_FP_OPS and PAPI_TOT_CYC events, and start the counters. Subsequent calls will read the counters and return total real time, total process time, total floating point operations, and the Mflops/s rate since the last call to PAPI_flops.
If PAPI_FP_OPS is a derived event in your platform, then your platform must have at least three counters to support PAPI_flops, because PAPI needs one counter to cycles. So in UltraSparcIII, even the platform supports PAPI_FP_OPS, but UltraSparcIII only has two available hardware counters and PAPI_FP_OPS is a derived event in this platform, so PAPI_flops returns an error.
