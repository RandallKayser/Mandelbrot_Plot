# Plot the Mandelbrot Set
### Current Status:
- Parameter Parsing from dat/(the\_run)/plotlist
- Routine to plot several parameters from one program call
- Continuous coloring based on (log) Potential
- Interior Detection method
- Next to no optimizations :)

### Current Goals:
- Binary search method
- Histogram based color palettes
- Seperate get\_logvs and build img in order to facilitate:
- Doing statistical analysis and modifications on logv data set
- Chunking pixel handling to prevent 100% ram utilization (and/or segfaults)
- Rudimentary 'image interest' estimation via discrete laplacian or Edge Detection Algorithms

### Future:
- Use logv stats and image interest heuristics to prune binary search
- Generate training set for CNN to generate image parameters
