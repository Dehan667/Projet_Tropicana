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
#include <wiringPi.h>

#define STR_BUFF 256
#define false 0
#define true 1

#include <unistd.h>
#include "k8055.h"

#define BUTTON1_CHANNEL 1
#define BUTTON2_CHANNEL 2
#define BUTTON3_CHANNEL 3
#define BUTTON4_CHANNEL 4
#define BUTTON5_CHANNEL 5

#define LED1_CHANNEL 1
#define LED2_CHANNEL 2
#define LED3_CHANNEL 3
#define LED4_CHANNEL 4
#define LED5_CHANNEL 5

int main(int argc, char *params[]) {
    int ipid = 0;

    // Ouvre le dispositif
    if (OpenDevice(ipid) < 0) {
        printf("Could not open the k8055 (port:%d)\nPlease ensure that the device is correctly connected.\n", ipid);
        return -1;
    }

    int button1_state = 0;
    int button2_state = 0;
    int button3_state = 0;
    int button4_state = 0;
    int button5_state = 0;

    while (1) {
        // Lit l'état des boutons
        int button1_read_state = ReadDigitalChannel(BUTTON1_CHANNEL);
        int button2_read_state = ReadDigitalChannel(BUTTON2_CHANNEL);
        int button3_read_state = ReadDigitalChannel(BUTTON3_CHANNEL);
        int button4_read_state = ReadDigitalChannel(BUTTON4_CHANNEL);
        int button5_read_state = ReadDigitalChannel(BUTTON5_CHANNEL);

        // Si le bouton 1 est pressé, allume ou éteint la LED 1
        if (button1_read_state == 1 && button1_state == 0) {
            printf("Vanne de la cuve, ouverte\n");
            button1_state = 1;
            SetDigitalChannel(LED1_CHANNEL);
        } else if (button1_read_state == 1 && button1_state == 1) {
            printf("Vanne de la cuve, fermer\n");
            button1_state = 0;
            ClearDigitalChannel(LED1_CHANNEL);
        }

        // Si le bouton 2 est pressé, allume ou éteint la LED 2
        if (button2_read_state == 1 && button2_state == 0) {
            printf("Vanne de la cuve de produit, ouverte\n");
            button2_state = 1;
            SetDigitalChannel(LED2_CHANNEL);
        } else if (button2_read_state == 1 && button2_state == 1) {
            printf("Vanne de la cuve de produit, fermer\n");
            button2_state = 0;
            ClearDigitalChannel(LED2_CHANNEL);
        }

        // Si le bouton 3 est pressé, allume ou éteint la LED 3
        if (button3_read_state == 1 && button3_state == 0) {
            printf("Vanne de l'eau publique, ouverte\n");
            button3_state = 1;
            SetDigitalChannel(LED3_CHANNEL);
        } else if (button3_read_state == 1 && button3_state == 1) {
            printf("Vanne de l'eau publique, fermer\n");
            button3_state = 0;
            ClearDigitalChannel(LED3_CHANNEL);
        }


        // Si le bouton 4 est pressé, allume ou éteint la LED 4
        if (button4_read_state == 1 && button4_state == 0) {
            printf("Tête de nettoyage BladeClean, en marche\n");
            button4_state = 1;
            SetDigitalChannel(LED4_CHANNEL);
        } else if (button4_read_state == 1 && button4_state == 1) {
            printf("Tête de nettoyage BladeClean, arrêter\n");
            button4_state = 0;
            ClearDigitalChannel(LED4_CHANNEL);
        }

        // Si le bouton 5 est pressé, allume ou éteint la LED 5
        if (button5_read_state == 1 && button5_state == 0) {
            printf("Tête de nettoyage TZ-74, en marche\n");
            button5_state = 1;
            SetDigitalChannel(LED5_CHANNEL);
        } else if (button5_read_state == 1 && button5_state == 1) {
            printf("Tête de nettoyage TZ-74, arrêter\n");
            button5_state = 0;
            ClearDigitalChannel(LED5_CHANNEL);
        }
    
        usleep(150000); // Attends 0.1 seconde avant de lire à nouveau l'état du bouton
    }

    // Ferme le dispositif
    CloseDevice();

    return 0;
}