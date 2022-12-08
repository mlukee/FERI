#include <iostream>
#include "Artwork.h"
#include "Artist.h"
#include "Gallery.h"
#include "Date.h"
#include "Painting.h"
#include "Sculpture.h"
#include <memory>

bool ascendingYear(std::shared_ptr<Artwork> i, std::shared_ptr<Artwork> j){
    if(i->getYear() <= j->getYear()) return true;
    return false;
}
bool descendingYear(std::shared_ptr<Artwork>i, std::shared_ptr<Artwork>j){
    if(i->getYear() >= j->getYear()) return true;
    return false;
}
bool ascendingPrice(std::shared_ptr<Artwork> i, std::shared_ptr<Artwork> j){
    if(i->getPrice() <= j->getPrice()) return true;
    return false;
}

bool isReaissanceArt(std::shared_ptr<Artwork>i){
    if(i->getYear() >= 1400 && i->getYear() <= 1600) return true;
    return false;
}

bool isOlderThan2000(std::shared_ptr<Artwork>art){
    if(art->getYear() < 2000) return true;
    return false;
}

int main()
{
    Gallery galerija("All you can imagine");
    Artist leonardo("Leonardo Da Vinci", "Zivel je v Italiji.", {15, 4, 1452});
    Artist vincentVanGogh("Vincent van Gogh", "he created about 2,100 artworks, including around 860 oil paintings...", {30, 3, 1853});
    Artist claudeMonet("Claude monet", "Oscar-Claude Monet was a French painter and founder of impressionist painting...", {14,7,1940});
    Artist gustavKlimt("Gustav Klimnt", "Some artist", {7,2,1876});

    Painting monaLisa("Mona Lisa", "Najznamenitejsa slika.", 10000, 1503, std::make_shared<Artist>(leonardo), PaintingTechnique::Oil);
    Painting nightSky("Starry Night", "The Starry Night is an oil-on-canvas painting", 10000, 1889, std::make_shared<Artist>(vincentVanGogh), PaintingTechnique::Graphite);
    Painting sunrise("Impression, Sunrise", "Impression, Sunrise is a painting by Claude Monet", 10000, 1872, std::make_shared<Artist>(claudeMonet), PaintingTechnique::Oil);
    Painting theKiss("The Kiss", "Extravagantly patterned", 7200, 1908, std::make_shared<Artist>(gustavKlimt), PaintingTechnique::Graphite);
    Sculpture david("David Statue", "Rand desc324245", 43456, 1567, std::make_shared<Artist>(leonardo), 1325, Material::Stone);

    galerija.addArtwork(std::make_shared<Painting>(monaLisa));
    galerija.addArtwork(std::make_shared<Painting>(nightSky));
    galerija.addArtwork(std::make_shared<Painting>(sunrise));
    galerija.addArtwork(std::make_shared<Painting>(theKiss));
    galerija.addArtwork(std::make_shared<Sculpture>(david));

    std::cout << galerija.toString();

    std::cout << "\nBefore filter: \n";
    std::cout << galerija.toString();
    galerija.filterOut(isOlderThan2000);
    std::cout << "\nAfter filter: \n";
    std::cout << galerija.toString();

    return 0;
}
