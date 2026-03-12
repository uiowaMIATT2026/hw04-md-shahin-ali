\# Difference of Gaussians (DOG)



\## Description

This module applies a Difference of Gaussians edge-enhancement filter.

DOG(f) = G\_sigma1(f) - G\_sigma2(f)

The output is rescaled to \[0, 255] and stored as unsigned char.



\## Effect of sigma1 and sigma2 on Edge Response



\### Small difference between sigma1 and sigma2 (e.g., sigma1=1.0, sigma2=1.5)

When sigma1 and sigma2 are close together, the DOG filter responds to fine,

high-frequency edges. Thin boundaries and small structures are highlighted.

However, the response is relatively weak and noisy regions may produce

many false edge detections.



\### Medium difference (e.g., sigma1=2.0, sigma2=3.5)

A moderate difference between sigmas produces a good balance. The filter

highlights medium-scale edges clearly, suppressing fine noise while still

detecting meaningful anatomical boundaries. This range works well for

brain MRI images where tissue boundaries are of primary interest.



\### Large difference between sigma1 and sigma2 (e.g., sigma1=1.0, sigma2=5.0)

A large difference makes the filter respond to coarse, large-scale edges only.

Fine details and thin boundaries are lost, but major structural boundaries

such as the boundary between white matter and gray matter are clearly visible.

The output appears simpler with fewer but stronger edge responses.



\### Effect of absolute sigma values

Using larger absolute values of both sigmas (e.g., sigma1=4.0, sigma2=6.0)

shifts the filter sensitivity toward larger anatomical structures, while

smaller absolute values (e.g., sigma1=0.5, sigma2=1.0) detect finer details.



\## Conclusion

By tuning sigma1 and sigma2, the DOG filter can be made sensitive to edges

at different spatial scales. For typical brain MRI analysis, sigma1=2.0 and

sigma2=3.5 provided clear edge detection of major tissue boundaries without

excessive noise sensitivity.

