// width = left to right
// depth = front to back
// height = top to bottom

bracketWidth = 33;
bracketDepth = 70;
overallHeight = 70;
frontThickness = 3.5;
sideThickness = 3.5;

dinSlotWidth = 30;
dinSlotHeight = 50;
dinSlotWallThickness = 3.5;
dinSlotOutsideHeight = (dinSlotWallThickness * 2) + dinSlotHeight;

$fn = 20;

module bracket() {
    translate([bracketWidth / 2, 0, overallHeight/2])
    {
    difference() {
        cube([bracketWidth, bracketDepth, overallHeight], center = true);
        translate([sideThickness, frontThickness, 0])
            cube([bracketWidth, bracketDepth, overallHeight + 1], center = true);
        

        
        translate([0, -bracketDepth / 2, -(overallHeight/2) + (overallHeight - dinSlotHeight - dinSlotWallThickness)])
        {
            // bottom slot
            union () {
                cube([10, 20, 6], center = true);
                translate([5, 0, 0])
                    rotate([90, 0, 0])
                        cylinder(h = 20, r = 3, center = true);
                translate([-5, 0, 0])
                    rotate([90, 0, 0])
                    cylinder(h = 20, r = 3, center = true);
            }

            // top slot left
            translate([0, 0, 15])
            union () {
                cube([10, 20, 5], center = true);
                translate([5, 0, 0])
                    rotate([90, 0, 0])
                        cylinder(h = 20, r = 2.5, center = true);
                translate([-5, 0, 0])
                    rotate([90, 0, 0])
                    cylinder(h = 20, r = 2.5, center = true);
            }

            // top slot right
            translate([0, 0, 22])
            union () {
                cube([10, 20, 5], center = true);
                translate([5, 0, 0])
                    rotate([90, 0, 0])
                        cylinder(h = 20, r = 2.5, center = true);
                translate([-5, 0, 0])
                    rotate([90, 0, 0])
                    cylinder(h = 20, r = 2.5, center = true);
            }
        }
    }
    }
    
    // side hole
    //translate([0, 30, overallHeight - dinSlotWallThickness - 25])
    //rotate([0, 90, 0])
    //cylinder (r = 2, h = 10, center = true);
    
}

module dinSleeve() {
    translate([-dinSlotWidth /2, 0, overallHeight - dinSlotOutsideHeight + (dinSlotOutsideHeight / 2)])
    difference() {
        cube([dinSlotWidth, bracketDepth, dinSlotOutsideHeight], center = true);
        translate([-.1, 0, 0])
            cube([dinSlotWidth + .2, bracketDepth + 1, dinSlotHeight], center = true);
        
    }
}

union() {
    bracket();
    dinSleeve();
}

