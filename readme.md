# Plot the Mandelbrot Set
### Current Status:
- Parameter Parsing from dat/(the\_run)/plotlist
- Routine to plot several parameters from one program call
- Continuous coloring based on (log) Potential
- Interior Detection method
- Next to no optimizations :)

### Current Goals:
- Remove all hardcoded filepaths, replace with full cmdline paths
- Binary search method
- Histogram based color palettes
- Doing statistical analysis and modifications on logv data set
- Gradient descent on l2 of (image) laplacian to optimize color parameters
- Chunking pixel handling to prevent 100% ram utilization (and/or segfaults)
- Rudimentary 'image interest' estimation via discrete laplacian or Edge Detection Algorithms
   - logv laplacian or image laplacian??
      - logv laplacian better for finding details; image for finding colorscheme
### Future:
- Use logv stats and image interest heuristics to prune binary search
- Generate training set for CNN to generate image parameters
