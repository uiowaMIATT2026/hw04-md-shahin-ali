// GaussianLPF - Gaussian low-pass filter for 3D NIFTI images
// Author: Md Shahin Ali (mali25)
// ECE:5490 HW04

// GaussianLPF.cxx
// ECE:5490 HW04 - Gaussian Low-Pass Filter
// Author: Md Shahin Ali (mali25)

#include "GaussianLPFCLP.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkRecursiveGaussianImageFilter.h"
#include "itkCastImageFilter.h"

int main(int argc, char* argv[])
{
  PARSE_ARGS;

  if (sigma <= 0.0)
  {
    std::cerr << "Error: sigma must be > 0. Got: " << sigma << std::endl;
    return EXIT_FAILURE;
  }

  using InputPixelType  = short;
  using RealPixelType   = float;
  using InputImageType  = itk::Image<InputPixelType, 3>;
  using RealImageType   = itk::Image<RealPixelType,  3>;
  using ReaderType      = itk::ImageFileReader<InputImageType>;
  using WriterType      = itk::ImageFileWriter<InputImageType>;
  using CastToRealType  = itk::CastImageFilter<InputImageType, RealImageType>;
  using CastToShortType = itk::CastImageFilter<RealImageType,  InputImageType>;
  using GaussianType    = itk::RecursiveGaussianImageFilter<RealImageType, RealImageType>;

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

  auto gaussX = GaussianType::New();
  gaussX->SetInput(castIn->GetOutput());
  gaussX->SetSigma(sigma);
  gaussX->SetDirection(0);
  gaussX->SetNormalizeAcrossScale(false);

  auto gaussY = GaussianType::New();
  gaussY->SetInput(gaussX->GetOutput());
  gaussY->SetSigma(sigma);
  gaussY->SetDirection(1);
  gaussY->SetNormalizeAcrossScale(false);

  auto gaussZ = GaussianType::New();
  gaussZ->SetInput(gaussY->GetOutput());
  gaussZ->SetSigma(sigma);
  gaussZ->SetDirection(2);
  gaussZ->SetNormalizeAcrossScale(false);

  auto castOut = CastToShortType::New();
  castOut->SetInput(gaussZ->GetOutput());

  auto writer = WriterType::New();
  writer->SetFileName(outputVolume);
  writer->SetInput(castOut->GetOutput());
  try { writer->Update(); }
  catch (const itk::ExceptionObject& e)
  {
    std::cerr << "Error writing: " << outputVolume << "\n" << e << std::endl;
    return EXIT_FAILURE;
  }

  std::cout << "GaussianLPF complete. Sigma=" << sigma << std::endl;
  return EXIT_SUCCESS;
}