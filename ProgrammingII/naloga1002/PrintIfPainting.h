#ifndef NALOGA1002_PRINTIFPAINTING_H
#define NALOGA1002_PRINTIFPAINTING_H

#include "Artwork.h"
#include <memory>

class PrintIfPainting {
public:
    void operator()(const std::shared_ptr<Artwork>& e);
};


#endif //NALOGA1002_PRINTIFPAINTING_H
