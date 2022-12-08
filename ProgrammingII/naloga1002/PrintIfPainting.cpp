#include "PrintIfPainting.h"
#include "Artwork.h"
#include "Painting.h"

void PrintIfPainting::operator()(const std::shared_ptr<Artwork>& e){
    //dynamic_cast(new_type)<ptr>
    if(std::dynamic_pointer_cast<std::shared_ptr<Painting>>(e))
        std::cout << e->toString() << std::endl << std::endl;
}
