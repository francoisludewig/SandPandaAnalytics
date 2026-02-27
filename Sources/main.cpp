#include "../Includes/Configuration/Option.h"
#include "../Includes/PackingFraction/PackingFractionProfileCalculator.h"
#include "../Includes/Repository/containerrepository.h"
#include "../Includes/Repository/sphererepository.h"

using namespace std;

int main(int argc,char **argv){
	SphereRepository sphr {};
	ContainerRepository ctr {};
	Option opt;
	if(opt.Management(argv,argc) == 0)
		return 0;

	sphr.load(opt.directory);
	ctr.load(opt.directory);

	PackingFractionProfileCalculator pfpc(ctr);
	pfpc.computePackingFractionProfile(sphr);
	pfpc.computePackingFraction();
	pfpc.exportProfiles(opt.directory);
	pfpc.exportPackingFractions(opt.directory);
	/*
	 * TODO
	 * (1) identifier le container : parallélipidède ou cylindrique
	 * (2) calcul de phi(z) par tranche dz du fond vers la surface
	 * (3.a) déterminer une zone stable sans effet de bord
	 * (3.b) calculer la moyenne de compacité sur cette zone
	 * (3.c) défninir la hauteur de l'empilement sur base du volume de grain de la compacité
	 * (3.d) confronter la valeur obtenue avec la surface libre de l'empilement
	 * (4) définir une hauteur par quantile à 5% ou 1% comme valeur limite
	 */


	return 0;
}
