#include <iostream>
#include "Artwork.h"
#include "Artist.h"
#include "Gallery.h"
#include "Date.h"
#include "Painting.h"
#include "Sculpture.h"

int main()
{
    Gallery galerija {"All you can imagine"};

    Artist * leonardo = new Artist{"Leonardo Da Vinci", "Zivel je v Italiji.", {15,4,1452}};
    Artist *vincentVanGogh = new Artist {"Vincent van Gogh", "he created about 2,100 artworks, including around 860 oil paintings...", {30, 3, 1853}};
    Artist *claudeMonet = new Artist {"Claude monet", "Oscar-Claude Monet was a French painter and founder of impressionist painting...", {14,7,1940}};
    Artist *gustavKlimt = new Artist {"Gustav Klimnt", "Some artist", {7,2,1876}};

    Artwork *monaLisa = new Painting{"Mona Lisa", "Najznamenitejsa slika.", 10000, 1503,leonardo, PaintingTechnique::Oil};
    Artwork *nightSky = new Painting{"Starry Night", "The Starry Night is an oil-on-canvas painting", 10000, 1889, vincentVanGogh, PaintingTechnique::Graphite};
    Artwork *sunrise = new Painting {"Impression, Sunrise", "Impression, Sunrise is a painting by Claude Monet", 10000, 1872, claudeMonet, PaintingTechnique::Oil};
    Artwork *theKiss = new Painting {"The Kiss", "Extravagantly patterned", 7200, 1908, gustavKlimt, PaintingTechnique::Graphite};
    Sculpture *david = new Sculpture{"David Statue", "Rand desc324245", 43456, 1567, vincentVanGogh, 1325, Material::Stone};

    galerija.addArtwork(monaLisa);
    galerija.addArtwork(nightSky);
    galerija.addArtwork(sunrise);
    galerija.addArtwork(theKiss);
    galerija.addArtwork(david);

    std::cout<<"--------------------------------------------------------------" << std::endl;
    std::cout << galerija.toString();
    std::cout<<"--------------------------------------------------------------" << std::endl;

    delete leonardo;
    delete vincentVanGogh;
    delete claudeMonet;
    delete gustavKlimt;
    delete monaLisa;
    delete nightSky;
    delete sunrise;
    delete theKiss;
    delete david;

    return 0;
}
