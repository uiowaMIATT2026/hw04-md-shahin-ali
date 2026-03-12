// CurvatureAD.cxx
// ECE:5490 HW04 - Curvature Anisotropic Diffusion Filter
// Author: Md Shahin Ali (mali25)

#include "CurvatureADCLP.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkCurvatureAnisotropicDiffusionImageFilter.h"
#include "itkCastImageFilter.h"

int main(int argc, char* argv[])
{
  PARSE_ARGS;

  using InputPixelType  = short;
  using RealPixelType   = float;
  using InputImageType  = itk::Image<InputPixelType, 3>;
  using RealImageType   = itk::Image<RealPixelType,  3>;
  using ReaderType      = itk::ImageFileReader<InputImageType>;
  using WriterType      = itk::ImageFileWriter<InputImageType>;
  using CastToRealType  = itk::CastImageFilter<InputImageType, RealImageType>;
  using CastToShortType = itk::CastImageFilter<RealImageType,  InputImageType>;
  using FilterType      = itk::CurvatureAnisotropicDiffusionImageFilter<RealImageType, RealImageType>;

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

  auto filter = FilterType::New();
  filter->SetInput(castIn->GetOutput());
  filter->SetConductanceParameter(conductance);
  filter->SetTimeStep(timeStep);
  filter->SetNumberOfIterations(iterations);

  auto castOut = CastToShortType::New();
  castOut->SetInput(filter->GetOutput());

  auto writer = WriterType::New();
  writer->SetFileName(outputVolume);
  writer->SetInput(castOut->GetOutput());
  try { writer->Update(); }
  catch (const itk::ExceptionObject& e)
  {
    std::cerr << "Error writing: " << outputVolume << "\n" << e << std::endl;
    return EXIT_FAILURE;
  }

  std::cout << "CurvatureAD complete. conductance=" << conductance
            << " timeStep=" << timeStep
            << " iterations=" << iterations << std::endl;
  return EXIT_SUCCESS;
}