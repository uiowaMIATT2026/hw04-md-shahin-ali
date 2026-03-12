\# Curvature Anisotropic Diffusion (CurvatureAD)



\## Description

This module applies curvature-based anisotropic diffusion filtering using

itk::CurvatureAnisotropicDiffusionImageFilter. Unlike gradient AD, curvature

AD uses the curvature of level-set contours as the diffusion measure, which

tends to produce smoother, more visually pleasing results.



\## Parameter Selection and Results



\### Conductance

Similar to gradient AD, lower conductance values preserve edges more strongly.

Curvature AD with conductance=2.0 produces noticeably smoother results than

gradient AD with the same conductance, with fewer staircasing artifacts.



\### Time Step

A time step of 0.0625 is recommended for 3D stability, same as gradient AD.



\### Number of Iterations

Curvature AD converges somewhat differently than gradient AD. With 10 iterations

and conductance=2.0, the output shows excellent noise reduction with smooth

appearance in homogeneous regions.



\## Comparison with Gradient AD

Curvature AD tends to produce smoother, more rounded edges compared to gradient

AD which preserves sharper but sometimes jagged boundaries. Curvature AD is

preferable when a smooth, clean appearance is desired. Gradient AD is preferable

when sharp edge preservation is the priority.



\## Recommended Parameters

After experimentation, the following parameters worked well on brain MRI data:

\- conductance = 2.0

\- timeStep = 0.0625

\- iterations = 10



These settings produced good noise reduction while keeping major anatomical

boundaries clearly visible.

