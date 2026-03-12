// DOG.cxx
// ECE:5490 HW04 - Difference of Gaussians Edge Filter
// Author: Md Shahin Ali (mali25)
// DOG(f) = G_sigma1(f) - G_sigma2(f), output rescaled to [0,255] unsigned char

#include "DOGCLP.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkRecursiveGaussianImageFilter.h"
#include "itkSubtractImageFilter.h"
#include "itkRescaleIntensityImageFilter.h"
#include "itkCastImageFilter.h"

using RealImageType = itk::Image<float, 3>;

static RealImageType::Pointer
ApplyGaussian3D(RealImageType* input, double sigma)
{
  using GaussianType = itk::RecursiveGaussianImageFilter<RealImageType, RealImageType>;

  auto gx = GaussianType::New();
  gx->SetInput(input);
  gx->SetSigma(sigma);
  gx->SetDirection(0);
  gx->SetNormalizeAcrossScale(false);

  auto gy = GaussianType::New();
  gy->SetInput(gx->GetOutput());
  gy->SetSigma(sigma);
  gy->SetDirection(1);
  gy->SetNormalizeAcrossScale(false);

  auto gz = GaussianType::New();
  gz->SetInput(gy->GetOutput());
  gz->SetSigma(sigma);
  gz->SetDirection(2);
  gz->SetNormalizeAcrossScale(false);
  gz->Update();

  return gz->GetOutput();
}

int main(int argc, char* argv[])
{
  PARSE_ARGS;

  if (sigma1 == sigma2)
  {
    std::cerr << "Error: sigma1 and sigma2 must be different." << std::endl;
    return EXIT_FAILURE;
  }

  using InputPixelType  = short;
  using OutputPixelType = unsigned char;
  using InputImageType  = itk::Image<InputPixelType,  3>;
  using OutputImageType = itk::Image<OutputPixelType, 3>;
  using ReaderType      = itk::ImageFileReader<InputImageType>;
  using WriterType      = itk::ImageFileWriter<OutputImageType>;
  using CastToRealType  = itk::CastImageFilter<InputImageType, RealImageType>;
  using SubtractType    = itk::SubtractImageFilter<RealImageType, RealImageType, RealImageType>;
  using RescaleType     = itk::RescaleIntensityImageFilter<RealImageType, OutputImageType>;

  auto reader = ReaderType::New();
  reader->SetFileName(inputVolume);
  try { reader->Update(); }
  catch (const itk::ExceptionObject& e)
  {
    std::cerr << "Error reading: " << inputVolume << "\n" << e << std::endl;
    return EXIT_FAILURE;
  }

  auto castIn = CastToRealType::New();
  castIn->SetInput(reader->GetOutput());
  castIn->Update();

  auto g1 = ApplyGaussian3D(castIn->GetOutput(), sigma1);
  auto g2 = ApplyGaussian3D(castIn->GetOutput(), sigma2);

  auto subtract = SubtractType::New();
  subtract->SetInput1(g1);
  subtract->SetInput2(g2);

  auto rescale = RescaleType::New();
  rescale->SetInput(subtract->GetOutput());
  rescale->SetOutputMinimum(0);
  rescale->SetOutputMaximum(255);

  auto writer = WriterType::New();
  writer->SetFileName(outputVolume);
  writer->SetInput(rescale->GetOutput());
  try { writer->Update(); }
  catch (const itk::ExceptionObject& e)
  {
    std::cerr << "Error writing: " << outputVolume << "\n" << e << std::endl;
    return EXIT_FAILURE;
  }

  std::cout << "DOG complete. sigma1=" << sigma1 << " sigma2=" << sigma2 << std::endl;
  return EXIT_SUCCESS;
}