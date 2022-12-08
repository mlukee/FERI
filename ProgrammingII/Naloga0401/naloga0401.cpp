#include <iostream>
#include "Artwork.h"
#include "Artist.h"
#include "Gallery.h"
#include "Date.h"

int main()
{
    Gallery galerija {"All you can imagine"};

    Artist * leonardo = new Artist{"Leonardo Da Vinci", "Zivel je v Italiji.", {15,4,1452}};
    Artist *vincentVanGogh = new Artist {"Vincent van Gogh", "he created about 2,100 artworks, including around 860 oil paintings...", {30, 3, 1853}};
    Artist *claudeMonet = new Artist {"Claude monet", "Oscar-Claude Monet was a French painter and founder of impressionist painting...", {14,7,1940}};
    Artist *pabloPicasso = new Artist{"Pablo Picasso", "Pablo Ruiz Picasso was a Spanish painter, sculptor, printmaker, ceramicist and theatre designer...", {25,10,1881}};
    Artist *michelangello = new Artist {"Michelangelo", "An Italian sculptor, painter, architect and poet of the High Renaissance.", {6,3,1475}};

    Artwork *monaLisa = new Artwork{"Mona Lisa", "Najznamenitejsa slika.", 10000, 1503,leonardo};
    Artwork *nightSky = new Artwork{"Starry Night", "The Starry Night is an oil-on-canvas painting", 10000, 1889, vincentVanGogh};
    Artwork *sunrise = new Artwork {"Impression, Sunrise", "Impression, Sunrise is a painting by Claude Monet", 10000, 1872, claudeMonet};
    Artwork *guernica = new Artwork {"Guernica", "Guernica is a large 1937 oil painting on canvas", 10000, 1937, pabloPicasso};
    Artwork *davidStatie = new Artwork {"David Statue", "David is a masterpiece of Renaissance sculpture, created in marble between 1501 and 1504 by the Italian artist Michelangelo.", 10000, 1504, michelangello};


    galerija.addArtwork(monaLisa);
    galerija.addArtwork(nightSky);
    galerija.addArtwork(sunrise);
    galerija.addArtwork(guernica);
    galerija.addArtwork(davidStatie);

    std::cout<<"--------------------------------------------------------------" << std::endl;
    std::cout << galerija.toString();
    std::cout<<"--------------------------------------------------------------" << std::endl;

    std::cout << "After deleting from gallery: " << std::endl;
    std::cout<<"--------------------------------------------------------------" << std::endl;
    galerija.removeArtwork(davidStatie);
    galerija.printArtworks();

    std::cout<<"--------------------------------------------------------------" << std::endl;
    std::cout << "Artworks between years: " << std::endl;
    std::cout<<"--------------------------------------------------------------" << std::endl;
    std::vector<Artwork*> artworks = galerija.getArtworksBetweenYear(1500, 1505);
    for (int i = 0; i < artworks.size(); ++i) {
        std::cout << artworks[i]->toString() << std::endl << std::endl;
    }

    delete leonardo;
    delete vincentVanGogh;
    delete claudeMonet;
    delete pabloPicasso;
    delete michelangello;
    delete monaLisa;
    delete nightSky;
    delete sunrise;
    delete davidStatie;
    delete guernica;
    return 0;
}
