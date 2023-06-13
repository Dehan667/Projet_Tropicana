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

#define POT1_CHANNEL 1   // Canal analogique du potentiomètre 1
#define POT2_CHANNEL 2   // Canal analogique du potentiomètre 2



int main(int argc, char *params[]) {
    int ipid = 3;

    // Ouvre le dispositif
    if (OpenDevice(ipid) < 3) {
        printf("Could not open the k8055 (port:%d)\nPlease ensure that the device is correctly connected.\n", ipid);
        return -1;
    }

    int button1_state = 0;
    int button2_state = 0;
    int button3_state = 0;
    int button4_state = 0;
    int button5_state = 0;
    int stock_value_1 = 300;
    int stock_value_2 = 300;


    while (1) {
        // Lit l'état des boutons
        int button1_read_state = ReadDigitalChannel(BUTTON1_CHANNEL);
        int button2_read_state = ReadDigitalChannel(BUTTON2_CHANNEL);
        int button3_read_state = ReadDigitalChannel(BUTTON3_CHANNEL);
        int button4_read_state = ReadDigitalChannel(BUTTON4_CHANNEL);
        int button5_read_state = ReadDigitalChannel(BUTTON5_CHANNEL);

        // Lit les valeurs des potentiomètres
        int pot1_value = ReadAnalogChannel(POT1_CHANNEL);
        int pot2_value = ReadAnalogChannel(POT2_CHANNEL);

        // Si le bouton 1 est pressé, allume ou éteint la LED 1 (vanne de la cuve)
        if (button1_read_state == 1 && button1_state == 0) {
            printf("Vanne de la cuve de produit, fermée\n");
            button1_state = 1;
            SetDigitalChannel(LED1_CHANNEL);
        } else if (button1_read_state == 1 && button1_state == 1) {
            printf("Vanne de la cuve de produit,ouvert\n");
            button1_state = 0;
            ClearDigitalChannel(LED1_CHANNEL);
        }

        // Si le bouton 2 est pressé, allume ou éteint la LED 2 (vanne de la cuve de produit)
        if (button2_read_state == 1 && button2_state == 0) {
            printf("Vanne du reseau l'eau, fermée\n");
            button2_state = 1;
            SetDigitalChannel(LED2_CHANNEL);
        } else if (button2_read_state == 1 && button2_state == 1) {
            printf("Vanne du reseau l'eau, ourvert\n");
            button2_state = 0;
            ClearDigitalChannel(LED2_CHANNEL);
        }

        // Si le bouton 3 est pressé, allume ou éteint la LED 3
        if (button3_read_state == 1 && button3_state == 0) {
            printf("Tête de nettoyage TZ-74, arrêtée\n");
            button3_state = 1;
            SetDigitalChannel(LED3_CHANNEL);
        } else if (button3_read_state == 1 && button3_state == 1) {
            printf("Tête de nettoyage TZ-74, en marche\n");
            button3_state = 0;
            ClearDigitalChannel(LED3_CHANNEL);
        }

        // Si le bouton 4 est pressé, allume ou éteint la LED 4
        if (button4_read_state == 1 && button4_state == 0) {
            printf("Tête de nettoyage BladeClean, arrêtée\n");
            button4_state = 1;
            SetDigitalChannel(LED4_CHANNEL);
        } else if (button4_read_state == 1 && button4_state == 1) {
            printf("Tête de nettoyage BladeClean, en marche\n");
            button4_state = 0;
            ClearDigitalChannel(LED4_CHANNEL);
        }

        // Si le bouton 5 est pressé, allume ou éteint la LED 5
        if (button5_read_state == 1 && button5_state == 0) {
            printf("Vanne de l'eau publique, fermée\n");
            button5_state = 1;
            SetDigitalChannel(LED5_CHANNEL);
        } else if (button5_read_state == 1 && button5_state == 1) {
            printf("Vanne de l'eau publique, ourvert\n");
            button5_state = 0;
            ClearDigitalChannel(LED5_CHANNEL);
        }

        // Affiche les valeurs des potentiomètres
        if (pot1_value != stock_value_1)
        {
            printf("Débitmètre de la cuve de produit: %dL\n", pot1_value/50);
        }
        if (pot2_value != stock_value_2)
        {
            printf("Débitmètre du reseau d'eau: %dL\n", pot2_value/4);
        }
        stock_value_1 = pot1_value;
        stock_value_2 = pot2_value;
    
        usleep(150000); // Attends 0.15 seconde avant de lire à nouveau l'état du bouton et les valeurs des potentiomètres
    }

    // Ferme le dispositif
    CloseDevice();

    return 0;
}

