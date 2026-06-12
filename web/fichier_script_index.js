let trajectoires   = {};
let positions      = {};
let indexAnimation = 0;

const FACTEUR_ECHELLE = 1e9;

/*
    Chargement du JSON
*/
async function chargerTrajectoires() {
    const response = await fetch("../data/data.json");

    trajectoires = await response.json();

    console.log("JSON chargé :", trajectoires);

    for (const nom in trajectoires)
        positions[nom] = 0;
}

function setup() {
    let canvas = createCanvas(800, 800);

    canvas.parent("canvas-container");

    chargerTrajectoires();
}

function dessinerSoleil() {
    fill(255, 255, 0);
    noStroke();
    circle(0, 0, 20);
}

function dessinerOrbites() {
    stroke(100);
    noFill();

    for (const nom in trajectoires) {
        beginShape();

        for (const point of trajectoires[nom]) {
            let position = point[0];

            let x = position[0] / FACTEUR_ECHELLE;
            let y = position[1] / FACTEUR_ECHELLE;

            vertex(x, y);
        }

        endShape();
    }
}

function dessinerPlanetes() {
    fill(0, 150, 255);
    noStroke();

    for (const nom in trajectoires) {
        let trajectoire = trajectoires[nom];

        if (trajectoire.length === 0)
            continue;

        let indice = indexAnimation % trajectoire.length;

        let position = trajectoire[indice][0];

        let x = position[0] / FACTEUR_ECHELLE;
        let y = position[1] / FACTEUR_ECHELLE;

        circle(x, y, 10);
    }
}

function draw() {
    background(0);

    translate(width / 2, height / 2);

    dessinerSoleil();
    dessinerOrbites();
    dessinerPlanetes();

    indexAnimation++;
}