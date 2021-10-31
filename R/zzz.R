#' RcppKyTea: 'Rcpp' Interface to 'KyTea'
#' @keywords internal
#' @import Rcpp
#' @useDynLib RcppKyTea, .registration=TRUE
"_PACKAGE"

#' @noRd
#' @param libpath libpath
.onUnload <- function(libpath) {
  library.dynam.unload("RcppKytea", libpath)
}
