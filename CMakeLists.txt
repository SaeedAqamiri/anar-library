project(anar)
cmake_minimum_required(VERSION 3.10)

add_library(anar Anar.cpp Engine.cpp PageModel.cpp Session.cpp VisitCollection.cpp)
