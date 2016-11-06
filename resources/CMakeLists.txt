#configure_file(planet.png bin/planet.png COPYONLY)

file(COPY ship.png DESTINATION ../bin)
file(COPY planet.png DESTINATION ../bin)
file(COPY bullet.png DESTINATION ../bin)
