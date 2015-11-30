/*! 
 *  \brief     CPU manufacturer, family and model detection
 *  \author    Katsileros Petros
 *  \date      29/10/2015
 *  \copyright 
 */

/**
* sources_intel: 
* 		https://software.intel.com/en-us/articles/intel-architecture-and-processor-identification-with-cpuid-model-and-family-numbers
*		http://a4lg.com/tech/x86/database/x86-families-and-models.en.html		
* sources_amd:
* 		https://en.wikipedia.org/wiki/List_of_AMD_CPU_microarchitectures
* 		https://en.wikipedia.org/wiki/List_of_AMD_microprocessors
* 		http://a4lg.com/tech/x86/database/x86-families-and-models.en.html
**/
#include <cstdio>
#include <cstring> 
#include <iostream>
#include <sstream>
#include <vector>


/**
@brief Test cpu brand (Intel / AMD)
@param output: CPU_Brand_ID = {Intel=1:99,AMD=101:200}
**/
int test_cpu_brand(int cpuid_brand)
{
		unsigned int ebx = 0, ecx = 0, edx = 0, eax = 0;
    
	#ifdef __linux
		__asm ("cpuid": "=b" (ebx), "=c" (ecx), "=d" (edx), "=a" (eax):"a" (eax));
		
		int regs[3] = {ebx,edx,ecx};
		char vendor[13];
		memcpy(vendor  , &regs[0], 4); // copy EBX
		memcpy(vendor+4, &regs[1], 4); // copy ECX
		memcpy(vendor+8, &regs[2], 4); // copy EDX
		vendor[12] = '\0';
		
	#elif _WIN32
		int reg[4];
		__cpuid((int *)reg, 0);
		eax = reg[0]; ebx = reg[1]; edx = reg[2]; ecx = reg[3];
		
		int regs[3] = {ebx,edx,ecx};
		char vendor[13];
		memcpy(vendor  , &regs[0], 4); // copy EBX
		memcpy(vendor+4, &regs[2], 4); // copy ECX
		memcpy(vendor+8, &regs[1], 4); // copy EDX
		vendor[12] = '\0';
	
	#else
		std::cout << "Not supported operating system" << std::endl;
	#endif
	
		
		//std::cout << "vendor: " << vendor << std::endl;
		
		if(!(strcmp(vendor,"GenuineIntel")))
		{
			std::cout << "CPU_BRAND: Intel" << std::endl;
			return 1;
		}
		else if(!(strcmp(vendor,"AuthenticAMD")))
		{
			std::cout << "CPU_BRAND: AMD" << std::endl;
			return 2;
		}
		else
		{
			std::cout << "Unknown CPU Brand" << std::endl;
			return 0;
		}
	
}

/**
@brief Test AMD CPU Family
@param output: {K8=15,K10=16,Bobcat=20,Bulldozer=21,Jaguar=22,Zen=23}
**/
int test_AMD_cpu_family(int cpuid_family)
{
	switch (cpuid_family)
    {
		case 0x17:
			std::cout << "CPU_family: Zen " << std::endl;
			return 106;
			break;
		case 0x16:
			std::cout << "CPU_family: Jaguar " << std::endl;
			return 105;
			break;
		case 0x15:
			std::cout << "CPU_family: Bulldozer " << std::endl;
			return 104;		
			break;
		case 0x14:
			std::cout << "CPU_family: Bobcat " << std::endl;
			return 103;
			break;
		case 0x10:
			std::cout << "CPU_family: K10 " << std::endl;
			return 102;
			break;
		case 0x0F:
			std::cout << "CPU_family: K8 " << std::endl;
			return 101;
			break;
		default:
			std::cout << "Unknown AMD CPU" << std::endl;
			return 0;
			break;
	}
}

/**
@brief Test Intel CPU Family
@param output: {family=6,Unknown=0}
**/
int test_Intel_cpu_family(int cpuid_family)
{
    switch (cpuid_family)
    {
        case 0x6:
			std::cout << "CPU_family: 0" << cpuid_family << std::endl;
            return 6;
            break;
        default:
			std::cout << "Unknown Intel CPU" << std::endl;
            return 0;
			break;
    }
}

/**
@brief Test Intel CPU Models (Architecture)
@param output: id of the model
**/
int test_Intel_cpu_model(int cpuid_model)
{
    switch (cpuid_model)
    {
        //Skylake - id_11
        case 0x5E:
			return 11;
            break;
        case 0x4E:
			return 11;
            break;

		 //silvermont - id_10
        case 0x4A:
			std::cout << "Architecture: Silvermont" << std::endl;
			return 10;
            break;
        case 0x4D:
			std::cout << "Architecture: Silvermont" << std::endl;
			return 10;
            break;
        case 0x5A:
			std::cout << "Architecture: Silvermont" << std::endl;
			return 10;
            break;

        //Broadwell - id_9
        case 0x4F:
			std::cout << "Architecture: Broadwell" << std::endl;
			return 9;
            break;
        case 0x3D:
			std::cout << "Architecture: Broadwell" << std::endl;
			return 9;
            break;

        //haswell - id_8
        case 0x3F:
			std::cout << "Architecture: Haswell" << std::endl;
			return 8;
            break;
        case 0x3C:
			std::cout << "Architecture: Haswell" << std::endl;
			return 8;
            break;
        case 0x46:
			std::cout << "Architecture: Haswell" << std::endl;
			return 8;
            break;
        case 0x45:
			std::cout << "Architecture: Haswell" << std::endl;
			return 8;
            break;

        //ivy bridge - id_7
        case 0x3E:
			std::cout << "Architecture: Ivy Bridge" << std::endl;
			return 7;
			break;
        case 0x3A:
			std::cout << "Architecture: Ivy Bridge" << std::endl;
			return 7;
			break;

        //sandy bridge - id_6
        case 0x2D:
			std::cout << "Architecture: Sandy Bridge" << std::endl;
			return 6;
			break;
        case 0x2A:
			std::cout << "Architecture: Sandy Bridge" << std::endl;
			return 6;
			break;
		  
        //bonnell - id_5
        case 0x1C:
			std::cout << "Architecture: Bonnell" << std::endl;
			return 5;
			break;
		case 0x27:
			std::cout << "Architecture: Bonnell" << std::endl;
			return 5;
			break;
		case 0x26:
			std::cout << "Architecture: Bonnell" << std::endl;
			return 5;
			break;
		case 0x35:
			std::cout << "Architecture: Bonnell" << std::endl;
			return 5;
			break;
		case 0x36:
			std::cout << "Architecture: Bonnell" << std::endl;
			return 5;
			break;
			
		//westmere - id_4
        case 0x2C:
			std::cout << "Architecture: Westmere" << std::endl;
			return 4;
			break;
        case 0x25:
			std::cout << "Architecture: Westmere" << std::endl;
			return 4;
			break;
		case 0x2F:
			std::cout << "Architecture: Westmere" << std::endl;
			return 4;
			break;

        //nehalem - id_3
        case 0x2E:
			std::cout << "Architecture: Nehalem" << std::endl;
			return 3;
			break;
        case 0x1E:
			std::cout << "Architecture: Nehalem" << std::endl;
			return 3;
			break;
        case 0x1A:
			std::cout << "Architecture: Nehalem" << std::endl;
			return 3;
			break;
			
		//penryn - id_2
		case 0x17:
			std::cout << "Architecture: Core (Penryn)" << std::endl;
			return 2;
			break;
		case 0x1D:
			std::cout << "Architecture: Core (Penryn)" << std::endl;
			return 2;
			break;
            
        //Merom - id_1
        case 0x0F:
			std::cout << "Architecture: Core (Merom)" << std::endl;
			return 1;
			break;
		case 0x16:
			std::cout << "Architecture: Core (Merom)" << std::endl;
			return 1;
			break;

        default:
			std::cout << "Unknown model" << std::endl;
			return 0;
			break;
    }
}


int main ()
{
	// Return Value
	int return_value = 0;
	
	// CPU Brand Check
	int cpu_brand_id = test_cpu_brand(0);
	
	/// Testing for AMD
	//cpu_brand_id = 2;
	
	// Assembly command registers
	unsigned int ebx = 0, ecx = 0, edx = 0, eax = 0;
	
	#ifdef _WIN32
		int reg[4];
		__cpuid((int *)reg, 1);
		eax = reg[0];
		
		int model = (eax  >> 4) & 0xF;
		int extended_model = (eax >> 16) & 0xF;
		int family_code = (eax >> 8)  & 0xF;
		int extended_family_code = (eax >> 20) & 0xFF;
		
	#else
		eax = 1;
		__asm ("cpuid": "=b" (ebx), "=c" (ecx), "=d" (edx), "=a" (eax):"a" (eax));
		
		int model = (eax & 0x0FF) >> 4;
		int extended_model = (eax & 0xF0000) >> 12;
		int family_code = (eax & 0xF00) >> 8;
		int extended_family_code = (eax & 0xFF00000) >> 16;
	
    #endif
	
	
	if(cpu_brand_id == 1) // Intel
	{
	    int cpuid_family = extended_family_code | family_code;
	    int cpu_family_id = 0;
	    cpu_family_id = test_Intel_cpu_family(cpuid_family);	
		if(cpu_family_id == 0)
	        return 0;
			
		//~ int stepping = (eax & 0x000000F);
		//~ std::cout << "Stepping: " << stepping << std::endl;
	
		int cpuid_model = extended_model | model;
		int cpu_model_id = 0;
		cpu_model_id = test_Intel_cpu_model(cpuid_model);
		if(cpu_model_id == 0)
				return 0;
		
		return_value = cpu_model_id;
		}
	else if(cpu_brand_id == 2) //AMD
	{   
		int cpuid_family = extended_family_code | family_code;
	    int cpu_family_id = 0;
	    /// Testing for AMD
	    //cpuid_family = 0x15;
	    cpu_family_id = test_AMD_cpu_family(cpuid_family);	
		if(cpu_family_id == 0)
	        return 0;
	    
	    return_value = cpu_family_id;
	}
	std::cout << "return code: " << return_value << std::endl;
	return return_value;
}
