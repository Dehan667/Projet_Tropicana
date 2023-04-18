/* $Id: main.c,v 1.3 2007/03/15 14:37:58 pjetur Exp $
 ***************************************************************************
 *   Copyright (C) 2004 by Nicolas Sutre                                   *
 *   nicolas.sutre@free.fr                                                 *
 *                                                                         *
 *   Copyright (C) 2005 by Bob Dempsey                                     *
 *   bdempsey_64@msn.com 						   *
 *									   *
 *   Copyright (C) 2005 by Julien Etelain and Edward Nys		   *
 *   Converted to C							   *
 *   Commented and improved by Julien Etelain <julien.etelain@utbm.fr>     *
 *                             Edward Nys <edward.ny@utbm.fr>              *
 *                                                                         *
 *   Copyleft (L) 2005 by Sven Lindberg					   *
 *   k8055@k8055.mine.nu						   *
 *   Give it up already :) Simplified (read improved..) and included 	   *
 *   with k8055 lib and with a functional man page			   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
 
#include <string.h>
#include <stdio.h>
#include <usb.h>
#include <assert.h>
#include <sys/time.h>
#include <k8055.h>

#define STR_BUFF 256
#define false 0
#define true 1

extern int DEBUG;


/*
	Convert a string on n chars to an integer
	Return  1 on sucess
			0 on failure (non number)
*/
int Convert_StringToInt(char *text, int *i)
{
	return sscanf(text, "%d", i);
}





/*
	Give current timestamp in miliseconds
*/
inline unsigned long int time_msec ( void ) {
	struct timeval t; struct timezone tz;
	gettimeofday (&t,&tz);
	return (1000*t.tv_sec)+(t.tv_usec/1000);
}


int main (int argc,char *params[]) 
{
	int ipid = 0;
	int valveState = 0;  // 0 = fermé, 1 = ouvert
	/*
		Search the device
	*/
	if ( OpenDevice(ipid)<0 ) {
		printf("Could not open the k8055 (port:%d)\nPlease ensure that the device is correctly connected.\n",ipid);
		return (-1);
		
	} else {
		
		    while (1) {
        valveState = ReadDigitalChannel(1);  // Lit l'état de la vanne connectée à l'entrée I1

        if (valveState == 1) {
            // La vanne est ouverte, allume la LED verte connectée à la sortie 8
            SetDigitalChannel(8);  // Allume la LED verte connectée à la sortie 8
        }
        else {
            // La vanne est fermée, allume la LED rouge connectée à la sortie 7
            ClearDigitalChannel(8);  // Éteint la LED verte connectée à la sortie 8
			
			valveState = ReadDigitalChannel(2);  // Lit l'état de la vanne connectée à l'entrée I2

        if (valveState == 1) {
            SetDigitalChannel(7);  // Allume la LED verte connectée à la sortie 6
        }
        else {
            // La vanne est fermée, allume la LED rouge connectée à la sortie 6
            ClearDigitalChannel(7);  // Éteint la LED verte connectée à la sortie 6
        }
					valveState = ReadDigitalChannel(3);  // Lit l'état de la vanne connectée à l'entrée I2

        if (valveState == 1) {
            SetDigitalChannel(6);  // Allume la LED verte connectée à la sortie 6
        }
        else {
            // La vanne est fermée, allume la LED rouge connectée à la sortie 6
            ClearDigitalChannel(6);  // Éteint la LED verte connectée à la sortie 6
        }

        }

        usleep(1000);  // Attends 1 seconde avant de lire à nouveau l'état de la vanne
    }
		

		
		
		CloseDevice();
	}
	
	return 0;
}