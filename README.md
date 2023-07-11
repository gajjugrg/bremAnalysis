# bremAnalysis
# Plotting functions for analysing the data
- [[plotSlices.C]]
	This function is for initial processing of the data. It takes the data and picks out the energy of interest and fills the tracklength/X_0 distribution 
	The output is slicesMC.ROOT

- [[overlay.C]]
	This function is to overlay and divide the MC and Analytical data points.
	The input is ana*.txt and slicesMC.ROOT

- [[plotTrackLenVsEne.C]]
	This function is to plot 2D histogram of Track length vs. Energy 

- [[comparePlot.C]]
	This function does the same thing as [[plotTrackLenVsEne.C]] 
