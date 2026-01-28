#include "../Includes/Configuration/Option.h"
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




	return 0;
}
