// [[Rcpp::plugins(cpp11)]]
// [[Rcpp::depends(RcppThread)]]
#define R_NO_REMAP
#define RCPPTHREAD_OVERRIDE_THREAD 1
#define HAVE_TR1_UNORDERED_MAP
#define KYTEA_SAFE

#include <Rcpp.h>
#include <RcppThread.h>
// #include <RcppParallel.h>
#include "kytea/kytea.h"
#include "kytea/kytea-struct.h"
#include "kytea/string-util.h"

using namespace Rcpp;
using namespace kytea;

// [[Rcpp::interfaces(r, cpp)]]
// [[Rcpp::export]]
List segment( const CharacterVector text, const std::string path ) {

    KyteaConfig * config = new KyteaConfig;
    config->setDebug(0);
    config->setEncoding("utf8");
    Kytea kytea(config);

    /* Load a KyTea model from a model file
       this can be a binary or text model in any character encoding,
       it will be detected automatically. */
    const char* file = R_ExpandFileName(path.c_str());
    if (!file) {
        Rcerr << "Failed to open the specified file. Check file path." << std::endl;
        return R_NilValue;
    }
    Rcout << "Loading model..." << std::endl;
    kytea.readModel(file);

    StringUtilUtf8 util;

    std::vector< std::vector<std::string> > res;
    for ( R_len_t i = 0; i < text.size(); i++ ) {
        // check user interrupt (Ctrl+C).
        if (i % 1000 == 0) checkUserInterrupt();

        const std::string tst = Rcpp::as<std::string>(text[i]);
        KyteaString surface_string = util.mapString(tst);
        KyteaSentence sentence(surface_string, util.normalize(surface_string));

        kytea.calculateWS(sentence);
        for( int t = 0; t < config->getNumTags(); t++) {
          kytea.calculateTags(sentence, t);
        }
        const KyteaSentence::Words words = sentence.words;

        std::vector< std::string > analyzed;
        for ( int j = 0; j < (int)words.size(); j++ ) {
            analyzed.push_back(util.showString(words[j].surface));
        }
        res.push_back(analyzed);
    }

    return List(wrap(res));
}
