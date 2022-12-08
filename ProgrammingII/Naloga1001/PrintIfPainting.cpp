#include "PrintIfPainting.h"
#include "Artwork.h"
#include "Painting.h"

void PrintIfPainting::operator()(Artwork *e) {
    //dynamic_cast(new_type)<ptr>
    if(dynamic_cast<Painting*>(e))
        std::cout << e->toString() << std::endl << std::endl;
}
