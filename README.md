# RcppKyTea

<!-- badges: start -->
[![Lifecycle: experimental](https://img.shields.io/badge/lifecycle-experimental-orange.svg)](https://lifecycle.r-lib.org/articles/stages.html#experimental)
<!-- badges: end -->

> 'Rcpp' Interface to 'KyTea'

'RcppKyTea' just tokenizes a character vector into tokens (a list of character vector)...that's all. This package does not provide interface to APIs for training models.

## Usage

You need [LIBLINEAR](https://www.csie.ntu.edu.tw/~cjlin/liblinear/) for installation.

```r
if (!requireNamespace("RcppKyTea")) remotes::install_github("paithiov909/RcppKyTea")

Sys.setenv(KYTEA_MODEL = "/path/to/the/kytea-model")
RcppKyTea::tokenize("これはテストです")
```

## License

MIT license.

This package includes works that are distributed under the Apache License, Version 2.0.

