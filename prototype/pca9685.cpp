#include <iostream>
#include <fstream>
#include <string>

// Sleep
#include <unistd.h>

const std::string driver = "/sys/class/pwm/pwmchip0/pwm12";

class IDevice
{
	public:
		virtual void set( std::string, int ) = 0;
};

class PWM:
	public IDevice
{
	public:
		PWM( std::string path ):
			mFileDevice( path ),
			mFilePeriod( path + "/period" ),
			mFileDutyCycle( path + "/duty_cycle" )
		{
			std::cout << "Construct PWM-Device\n";
		}
		
		void set( std::string _property, int _setpoint )
		{
			std::ofstream file;
			std::cout << "set " << _property << " : " << _setpoint << "\n";

			if ( _property.compare( "period" ) == 0 )
			{
				file.open( mFilePeriod, std::ios::out );
			}
			else if ( _property.compare( "dutycycle" ) == 0 )
			{
				file.open( mFileDutyCycle, std::ios::out );
			}
			else
			{
				std::cerr << "Unknown property\n";
				return;
			}

			if ( file.is_open() )
  			{
				file << _setpoint;
				file.close();
			}
  			else 
				std::cerr << "Unable to open file\n";
		}

	private:
		const std::string mFileDevice;
		const std::string mFilePeriod;
		const std::string mFileDutyCycle;
};


int main()
{
	const int step = 7500;
	const int speed = 5000;
	const int min = 450000;
	const int max = 2300000;	

	int setpoint;
	std::cout << "Prototype: PWM Controller demo\n";

	std::cout << "Control PWM signal [" << driver << "]\n";

	// If fails, you might need to open 12 with export t
	// "echo 12 > /sys/class/pwm/pwmchip0/export"

	std::cout << "Create new PWM device\n";
	IDevice *pwm = new PWM( driver );

	std::cout << "Configure the period\n";
	pwm->set( "period" , 20000000 );
	usleep( 1000 );       	

	while ( 1 )
	{
		std::cout << "Move forward\n";
		for ( setpoint = min; setpoint <= max; setpoint += step )
		{
			pwm->set( "dutycycle" , setpoint );
			usleep( speed );       	
		}

		std::cout << "Move backward\n";
		for ( setpoint = max; setpoint >= min; setpoint -= step )
		{
			pwm->set( "dutycycle" , setpoint );
			usleep( speed );       	
		}
	}
}
