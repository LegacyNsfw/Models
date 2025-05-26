pcmWidth = 228;
pcmDepth = 169-1;
pcmLowerClampHeight = 22;
pcmUpperClampHeight = 27;
sidePadding = 2; // 15;
connectorPadding = 15;
backPadding = 2;

overallWidth = pcmWidth + (2 * sidePadding);
overallDepth = pcmDepth + connectorPadding + backPadding;
overallHeight = pcmUpperClampHeight + 5;

connectorWidth = 175;

$fn = 20;

module boss() {
  cylinder(overallHeight, 7, 7);
}

module boltHole() {
  translate([0, 0, -0.5])
    cylinder(overallHeight + 1, 2.5, 2.5);
}

module boltHoles() {
  translate([overallWidth/2 + 1, 35, 0])
    boltHole();

  translate([-overallWidth/2 - 1, 35, 0])
    boltHole();

  translate([0, overallDepth + 1, 0])
    boltHole();
}

module outside() {
  translate([-overallWidth/2, 0, 0])
    cube([overallWidth, overallDepth, overallHeight]);
    
  translate([overallWidth/2 + 1, 35, 0])
    boss();

  translate([-overallWidth/2 - 1, 35, 0])
    boss();

  translate([0, overallDepth + 1, 0])
    boss();
}

module cutout() {
  translate([0, connectorPadding+4, 0])//pcmUpperClampHeight])
  linear_extrude(200)
  polygon(
    points=[
      [0,0],
      [105,0],
      [105,22],
      [pcmWidth / 2,22],
      [pcmWidth / 2,42],
      [105,42],
      [105,154],
      [-105,154],
      [-105,42],
      [-pcmWidth / 2,42],
      [-pcmWidth / 2,22],
      [-105,22],
      [-105,0],
      ],
      paths=[[0,1,2,3,4,5,6,7,8,9,10,11,12,0]]);
}

module base() {
  union() {
    //translate([-pcmWidth / 2, connectorPadding, -0.01])
    translate([0, pcmDepth / 2 + connectorPadding, pcmUpperClampHeight / 2 - 0.01])
      cube([pcmWidth, 140, pcmUpperClampHeight], center = true);
      
    translate([0, pcmDepth / 2 + connectorPadding, pcmLowerClampHeight / 2 - 0.01])
      cube([pcmWidth, pcmDepth, pcmLowerClampHeight], center = true);
  }
}

module connector() {
    // 9mm from base to bottom of connector housing
  translate([-connectorWidth/2, -1, -1])
    cube([connectorWidth, 50, 50]);
}

module truncate() {
  translate([-pcmWidth/2 -10, -1, -1])
    cube([200, 500, 50]);
}

difference() {
    outside();
    boltHoles();
    base();
    cutout();
    connector();
//    truncate();
}    
    
