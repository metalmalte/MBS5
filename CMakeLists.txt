cmake_minimum_required(VERSION 2.8.4)
project(MIPExercise5)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    src/BallStructureElement.cpp
    src/BallStructureElement.h
    src/BinaryThresholdFilter.cpp
    src/BinaryThresholdFilter.h
    src/BinomialKernel.cpp
    src/BinomialKernel.h
    src/ClosingFilter.cpp
    src/ClosingFilter.h
    src/ContrastStretchingFilter.cpp
    src/ContrastStretchingFilter.h
    src/ConvolutionFilter.cpp
    src/ConvolutionFilter.h
    src/ConvolutionKernel.cpp
    src/ConvolutionKernel.h
    src/DilationFilter.cpp
    src/DilationFilter.h
    src/ErosionFilter.cpp
    src/ErosionFilter.h
    src/GaussianKernel.cpp
    src/GaussianKernel.h
    src/Image.cpp
    src/Image.h
    src/ImageFilter.cpp
    src/ImageFilter.h
    src/ImageHistogram.cpp
    src/ImageHistogram.h
    src/ImageIO.cpp
    src/ImageIO.h
    src/LaplaceKernel.cpp
    src/LaplaceKernel.h
    src/MeanKernel.cpp
    src/MeanKernel.h
    src/MIPSegmentationEvaluation.cpp
    src/MIPVentricleSegmentation.cpp
    src/OpeningFilter.cpp
    src/OpeningFilter.h
    src/RegionGrowingFilter.cpp
    src/RegionGrowingFilter.h
    src/ShiftScaleFilter.cpp
    src/ShiftScaleFilter.h
    src/SobelFilter.cpp
    src/SobelFilter.h
    src/StructureElement.cpp
    src/StructureElement.h
    src/UnsharpMaskKernel.cpp
    src/UnsharpMaskKernel.h
    src/WindowLevelFilter.cpp
    src/WindowLevelFilter.h)

add_executable(MIPExercise5 ${SOURCE_FILES})