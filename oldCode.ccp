/*
//
//   Below Redraws city landscape
*/

for (int i = 0; i < getSize(missileDLL); i++) {
    if (i == 0) {
        eMissile = (MISSILE*)getHead(missileDLL);
    } else {
        eMissile = (MISSILE*)getNext(missileDLL);
    }
    for (int k = 0; k < numCity; k++) {
        ourCity = city_get_info(k);
        if (ourCity.status == DESTORIED) break;
        if ( eMissile->x >= ourCity.x && eMissile->x <= ourCity.x + ourCity.width) {
            if ( eMissile->y <= ourCity.y && eMissile->y >= ourCity.y - ourCity.height) {
                pc.printf("CITYGONE\n");
                // create little explosion from impact
                bigBang(eMissile->x,eMissile->y);
                city_destory(k);
                eMissile->status = MISSILE_EXPLODED;
                playSound("/sd/shotQ.wav");
                break;
            }
        }
    }
}


for (int i = 0; i < numCity; i++) {
    ourCity = city_get_info(i);
    if (ourCity.status == DESTORIED) break;
    for (int j = 0; j < getSize(missileDLL); j++) {
        if (j == 0) {
            eMissile = (MISSILE*)getHead(missileDLL);
        } else {
            eMissile = (MISSILE*)getNext(missileDLL);
        }
        if ( eMissile->x >= ourCity.x && eMissile->x <= ourCity.x + ourCity.width) {
            if ( eMissile->y <= ourCity.y && eMissile->y >= ourCity.y - ourCity.height) {
                pc.printf("CITYGONE\n");
                // create little explosion from impact
                bigBang(eMissile->x,eMissile->y);
                city_destory(i);
                eMissile->status = MISSILE_EXPLODED;
                playSound("/sd/shotQ.wav");
                break;
            }
        }
    }
}
 /*
//
//   Checks if the game is over
//
*/

// Checking if plane has been hit
for ( int i  = 0; i < getSize(missileDLL); i++) {
    if (i == 0) {
            eMissile = (MISSILE*)getHead(missileDLL);
        } else {
            eMissile = (MISSILE*)getNext(missileDLL);
        }
    if ( eMissile->x >= player.x && eMissile->x <= player.x + player.width) {
        if ( eMissile->y <= player.y && eMissile->y >= player.y - player.height) {
            player_destroy();
            playSound("/sd/shotQ.wav");
            eMissile->status = MISSILE_EXPLODED;
            planeHit = 1;
            break;
        }
    }
}
