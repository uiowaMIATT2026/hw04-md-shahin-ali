// SimpleThreshold - Binary threshold filter for 3D NIFTI images
// Author: Md Shahin Ali (mali25)
// ECE:5490 HW04

// SimpleThreshold.cxx
// ECE:5490 HW04 - Binary Threshold Filter
// Author: Md Shahin Ali (mali25)

#include "SimpleThresholdCLP.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkBinaryThresholdImageFilter.h"

int main(int argc, char* argv[])
{
  PARSE_ARGS;

  using PixelType  = short;
  using ImageType  = itk::Image<PixelType, 3>;
  using ReaderType = itk::ImageFileReader<ImageType>;
  using WriterType = itk::ImageFileWriter<ImageType>;
  using FilterType = itk::BinaryThresholdImageFilter<ImageType, ImageType>;

  auto reader = ReaderType::New();
  reader->SetFileName(inputVolume);
  try { reader->Update(); }
  catch (const itk::ExceptionObject& e)
  {
    std::cerr << "Error reading: " << inputVolume << "\n" << e << std::endl;
    return EXIT_FAILURE;
  }

  auto filter = FilterType::New();
  filter->SetInput(reader->GetOutput());
  filter->SetLowerThreshold(static_cast<PixelType>(lowThreshold));
  filter->SetUpperThreshold(static_cast<PixelType>(highThreshold));
  filter->SetOutsideValue(static_cast<PixelType>(outsideValue));
  filter->SetInsideValue(static_cast<PixelType>(insideValue));

  auto writer = WriterType::New();
  writer->SetFileName(outputVolume);
  writer->SetInput(filter->GetOutput());
  try { writer->Update(); }
  catch (const itk::ExceptionObject& e)
  {
    std::cerr << "Error writing: " << outputVolume << "\n" << e << std::endl;
    return EXIT_FAILURE;
  }

  std::cout << "SimpleThreshold complete." << std::endl;
  return EXIT_SUCCESS;
}