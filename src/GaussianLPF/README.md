\# Gaussian Low-Pass Filter (GaussianLPF)



\## Description

This module applies a 3D Gaussian low-pass filter using itk::RecursiveGaussianImageFilter

with the same sigma value applied in the X, Y, and Z directions.



\## Effect of Sigma on Smoothing and Resolution



\### Small sigma (sigma = 0.5 - 1.0)

With small sigma values, the filter applies very mild smoothing. High-frequency noise

is only slightly reduced, and fine image details and edges are well preserved. The output

image looks very similar to the input, with only subtle blurring visible.



\### Medium sigma (sigma = 2.0 - 3.0)

At medium sigma values, noise reduction becomes clearly visible. Random intensity

variations in homogeneous regions are smoothed out effectively. However, edges and

boundaries between tissue types begin to blur noticeably. Small anatomical structures

may lose definition at this level.



\### Large sigma (sigma = 5.0 or greater)

Large sigma values produce heavy smoothing. Most noise is eliminated but at the cost

of significant loss of image resolution. Edges become very blurry, small structures

may disappear entirely, and fine anatomical details are lost. The image takes on a

soft, washed-out appearance.



\## Conclusion

There is a clear tradeoff between noise reduction and preservation of image resolution.

Smaller sigma values preserve edges but leave more noise. Larger sigma values remove

noise effectively but blur important anatomical boundaries. For brain MRI images, a

sigma of around 1.0 to 2.0 provides a reasonable balance between smoothing and

detail preservation.

