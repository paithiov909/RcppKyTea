#' Tokenize text using KyTea
#' @param text Character vector.
#' @param model Path to model file.
#' @returns List of character vectors.
#' @export
tokenize <- function(text,
                     model = Sys.getenv("KYTEA_MODEL")) {
  text <- enc2utf8(text)
  res <- segment(text, model)
  lapply(res, function(elem) {
    Encoding(elem) <- "UTF-8"
    return(elem)
  })
}
