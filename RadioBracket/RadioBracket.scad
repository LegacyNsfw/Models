gaugeDiameter = 52.8; // 52.4 was too small
gaugeRadius = gaugeDiameter / 2;

module gauge() {
    rotate([90, 0, 0]) {
    cylinder (r = gaugeRadius, h = 20, center = true);
    //cylinder (r = 31, h = 10, center = true);
    }
}

module gauges() {
    color("red") {
        translate([1.5, 0, -16]) {
                
            translate([-54, 0, 3]) 
            gauge();
            
            translate([54, 0, 3])
            gauge();
                
            translate([0, 0, 34])
            gauge();
        }
    }
}


$fn = 50;

// width = left to right
// depth = front to back
// height = top to bottom

boxInsideWidth = 186;
boxDepth = 15;
earWidth = 30;
earThickness = 3.5;
earHeight = 45;
overallWidth = boxInsideWidth + 2 * earWidth;

boxInsideHeight = 93;
boxWallThickness = 3.5;
boxOutsideHeight = (boxWallThickness * 2) + boxInsideHeight;

// boxOutsideWidth = 183;
boxOutsideWidth = (boxWallThickness * 2) + boxInsideWidth;


//gaugeD = 52.8; // 52.4 was too small
//gaugeR = gaugeD / 2;

slotWidth = 5;


module box()
{
    translate([0, boxDepth / 2, 0])    
    {
        difference ()
        {
            cube([boxOutsideWidth, boxDepth, boxOutsideHeight], center = true);
            translate([0, boxWallThickness, 0])
            cube([boxInsideWidth, boxDepth, boxInsideHeight], center = true);
        }
    }
}

module ear(y, slotX)
{
    difference() {
        translate([0, earThickness / 2, 0])    
            cube([earWidth, earThickness, earHeight], center = true);
        
        a = -y + 1 ; //-y + boxOutsidthHeight / 2 - 55;
        translate([slotX, 0, -y + 1])
        {
            // bottom slot
            union () {
                cube([slotWidth, 20, 6.5], center = true);
                translate([slotWidth/2, 0, 0])
                    rotate([90, 0, 0])
                        cylinder(h = 20, r = 3.25, center = true);
                translate([-slotWidth/2, 0, 0])
                    rotate([90, 0, 0])
                    cylinder(h = 20, r = 3.25, center = true);
            }

            // middle slot (used on right side)
            translate([0, 0, 13])
            union () {
                cube([slotWidth, 20, 5], center = true);
                translate([slotWidth/2, 0, 0])
                    rotate([90, 0, 0])
                        cylinder(h = 20, r = 2.5, center = true);
                translate([-slotWidth/2, 0, 0])
                    rotate([90, 0, 0])
                    cylinder(h = 20, r = 2.5, center = true);
            }

            // top slot (used on left side)
            translate([0, 0, 21.5])
            union () {
                cube([slotWidth, 20, 5], center = true);
                translate([slotWidth/2, 0, 0])
                    rotate([90, 0, 0])
                        cylinder(h = 20, r = 2.5, center = true);
                translate([-slotWidth/2, 0, 0])
                    rotate([90, 0, 0])
                    cylinder(h = 20, r = 2.5, center = true);
            }
        }        
    }
}



color("yellow") {
    difference() {
        box();
        gauges();
    }

    // Ear position is fixed regardless of box size
    earX = 183 / 2 + earWidth / 2;
    earSlotX = 6.5;
    earY = boxOutsideHeight / 2 - earHeight / 2 - 15;
    
    translate([earX, 0, earY])
        ear(earY, earSlotX);
    translate([-earX, 0, earY])
        ear(earY, -earSlotX);
}