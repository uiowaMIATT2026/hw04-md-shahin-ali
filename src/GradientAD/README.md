\# Gradient Anisotropic Diffusion (GradientAD)



\## Description

This module applies gradient-based anisotropic diffusion filtering using

itk::GradientAnisotropicDiffusionImageFilter. The filter smooths homogeneous

regions while preserving edges by using the image gradient as a conductance measure.



\## Parameter Selection and Results



\### Conductance

Low conductance values (0.5 - 1.0) make the filter highly edge-sensitive.

Smoothing is mostly confined to flat homogeneous regions and very little

diffusion occurs across edges. High conductance values (3.0 - 5.0) allow

diffusion across edges, producing more uniform smoothing but at the cost

of edge blurring.



\### Time Step

The time step controls the rate of diffusion per iteration. For 3D images,

a time step of 0.0625 is the recommended stable value. Larger time steps

may cause numerical instability and produce artifacts.



\### Number of Iterations

More iterations produce stronger smoothing. With 5 iterations, mild smoothing

is achieved. With 10-20 iterations, noise is substantially reduced while edges

are still reasonably preserved. Beyond 30 iterations, even strong edges begin

to erode.



\## Recommended Parameters

After experimentation, the following parameters achieved good smoothing

without excessive edge degradation on brain MRI data:

\- conductance = 2.0

\- timeStep = 0.0625

\- iterations = 10



These settings effectively reduce noise in white matter regions while

keeping the boundaries between gray matter, white matter, and CSF sharp.

