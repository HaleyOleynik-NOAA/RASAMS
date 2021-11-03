# Load RASAMS module -------------------------------------------------------------------------
.onLoad <- function(libname, pkgname) {
  print("loading RASAMS")
  library.dynam("RASAMS", pkgname, libname)
  
}

.LastLib <- function(libpath)
{
  print("unloading RASAMS")
  library.dynam.unload("RASAMS", libpath)
}