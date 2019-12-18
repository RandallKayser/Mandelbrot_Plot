# Plot the Mandelbrot Set
### Current Status:
- Parameter Parsing from dat/(the\_run)/plotlist
- Continuous coloring based on (log) Potential
- Next to no optimizations :)

### Current Goals:
- Seperate geti\_logvs and build img in order to facilitate:
- Doing statistical analysis and modifications on logv data set
- Chunking pixel handling to prevent 100% ram utilization (and/or segfaults)
- Rudimentary 'image interest' estimation via discrete laplacian or Edge Detection Algorithms

### Future:
- Use logv stats and image interest heuristics to prune binary search
- Generate training set for CNN to generate image parameters
