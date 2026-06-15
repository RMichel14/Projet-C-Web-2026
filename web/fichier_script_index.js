// Documentation bibliothèque P5.js : https://p5js.org/reference/

/**********************************************
 ************ Variables globales **************
 **********************************************/

let trajectoires     = {};   // contenu du fichier JSON
let indexAnimation   = 0;    // variable de mise à jour du temps
let animationActive  = true; // variable pour le bouton "pause"
let zoom             = 1;    // zoom du canva par défaut

// Affichage des planètes
let planetesVisibles = {};   // liste des planètes visibles sur le canva


/**********************************************
 ***************** Constantes *****************
 **********************************************/

let FACTEUR_ECHELLE  = 1e9;
const couleurs = {
    "mercure-euler": "#B5B5B5",
    "venus-euler":   "#E0C16C",
    "earth-euler":   "#4AA3FF",
    "mars-euler":    "#D95C37",
    "jupiter-euler": "#D2A679",
    "saturne-euler": "#E8D7A5",
    "uranus-euler":  "#8BE9FD",
    "neptune-euler": "#4169E1"
};
const nomPlanetes = {
    "mercure-euler": "Mercure",
    "venus-euler":   "Vénus",
    "earth-euler":   "Terre",
    "mars-euler":    "Mars",
    "jupiter-euler": "Jupiter",
    "saturne-euler": "Saturne",
    "uranus-euler":  "Uranus",
    "neptune-euler": "Neptune"
};

/**
 * Utilisation de preload() propre à p5.js pour bloquer l'exécution tant que le JSON n'est pas là
 */
function preload() {
    trajectoires = loadJSON("../data/data.json"); // charge le JSON de manière synchrone avant setup()
}

/**
 * Fonction de la bibliothèque P5.js pour paramétrer le canva
 */
function setup() {
    let canvas = createCanvas(800, 500);
    canvas.parent("canvas-container");

    // Appel des fonctions d'initialisation de l'interface utilisateur
    initialiserFiltres();
    calculerEchelleAutomatique();
    initialiserEvenementsBoutons();
}

/**
 * Permet de calculer dynamiquement l'échelle utilisée sur le canva pour une meilleure lisibilité
 */
function calculerEchelleAutomatique() {
    let distanceMax = 0;

    for (const nom in trajectoires) {
        // Si la planète n'est pas cochée/visible, on ne la compte pas dans l'échelle
        if (planetesVisibles[nom] === false)
            continue;

        for (const point of trajectoires[nom]) {
            const position = point[0];
            const distance = Math.sqrt(position[0] ** 2 + position[1] ** 2); // racine_carrée(position1² + position2²)

            if (distance > distanceMax)
                distanceMax = distance;
        }
    }

    // Au cas où aucune planète n'est sélectionnée
    if (distanceMax > 0 && width > 0)
        FACTEUR_ECHELLE = distanceMax / (width * 0.4);
}

/**
 * Fonction pour ajouter un listener sur chaque champs "input" du sélecteur de planètes
 */
function ajouterListenersCheckbox() {
    document
        .querySelectorAll("#planetFilters input")
        .forEach(checkbox => {
            checkbox.addEventListener("change", function () {
                const nom = this.dataset.planet;
                planetesVisibles[nom] = this.checked;
                calculerEchelleAutomatique();
            });
        });
}

/**
 * Fonction qui permet d'ajouter les planètes (champs "input") dynamiquement dans le sélecteur de planètes
 */
function initialiserFiltres() {
    const container = document.getElementById("planetFilters");
    if (!container) return;

    container.innerHTML = "";

    for (const nom in trajectoires) {
        planetesVisibles[nom] = true;

        const label = document.createElement("label");
        label.className = "planetCheckbox";
        label.innerHTML = `
            <input type="checkbox" checked data-planet="${nom}">
            <span>${nomPlanetes[nom] || nom}</span>
        `;

        container.appendChild(label);
    }

    ajouterListenersCheckbox();
}

/**
 * Fonction pour initialiser les différents boutons de la page // ajouts des listener sur chaque et recalcul de l'échelle
 */
function initialiserEvenementsBoutons() {
    const pauseBtn = document.getElementById("pauseBtn");
    if (pauseBtn) {
        pauseBtn.addEventListener("click", () => {
            animationActive = !animationActive;
            pauseBtn.textContent = animationActive ? "Pause" : "Reprendre";
        });
    }

    const selectAllBtn = document.getElementById("selectAllBtn");
    if (selectAllBtn) {
        selectAllBtn.addEventListener("click", () => {
            document.querySelectorAll("#planetFilters input").forEach(cb => {
                cb.checked = true;
                planetesVisibles[cb.dataset.planet] = true;
            });
            calculerEchelleAutomatique();
        });
    }

    const clearAllBtn = document.getElementById("clearAllBtn");
    if (clearAllBtn) {
        clearAllBtn.addEventListener("click", () => {
            document.querySelectorAll("#planetFilters input").forEach(cb => {
                cb.checked = false;
                planetesVisibles[cb.dataset.planet] = false;
            });
            calculerEchelleAutomatique();
        });
    }
}

function dessinerSoleil() {
    fill(255, 255, 0);    // définit que toute forme dessinée ensuite sera de couleur jaune
    circle(0, 0, 20);     // trace un cercle -- argument : circle(largeur, hauteur, diamètre)
}

function dessinerOrbites() {
    stroke(100);          // définit la couleur utilisée pour tracer les points, les lignes et les contours des formes
    noFill();             // rend le remplissage complètement transparent

    for (const nom in trajectoires) {
        if (!planetesVisibles[nom])
            continue;

        beginShape();     // début de la forme -- commence à ajouter des sommets à cette forme

        for (const point of trajectoires[nom]) {
            let position = point[0];
            let x = position[0] / FACTEUR_ECHELLE;
            let y = position[1] / FACTEUR_ECHELLE;
            vertex(x, y); // définit les coordonnées d'un sommet entre les instructions beginShape() et endShape()
        }
        endShape();       // fin de la forme
    }
}

function dessinerPlanetes() {
    noStroke(); // désactive le tracé de point, de lignes et de contours de formes

    for (const nom in trajectoires) {
        if (!planetesVisibles[nom])
            continue;

        let trajectoire = trajectoires[nom];
        if (!trajectoire || trajectoire.length === 0)
            continue;

        let indice   = indexAnimation % trajectoire.length;
        let position = trajectoire[indice][0];

        let x = position[0] / FACTEUR_ECHELLE;
        let y = position[1] / FACTEUR_ECHELLE;

        fill(couleurs[nom] || "white"); // définit que toute forme ou trait sera tracé de la couleur passée en paramètre
        circle(x, y, 10);               // définit un cercle à la position horizontale en x et verticale en y, le diamètre est de 10px

        fill(255);                      // la suite des instructions seront de couleur blanche
        textSize(12);                   // définit la taille du texte lorsque la fonction text() est appelée
        text(nomPlanetes[nom] || nom, x + 8, y - 8); // écrit le texte passé en premier argument, à la position x et y (coin inférieur gauche du texte) (ici, écrit à droite de la planète, légèrement au-dessus)
    }
}

function mouseWheel(event) {
    /**
     * event.delta permet de savoir si l'action est de zoomer (valeur: -100) ou de dézoomer (valeur: 100)
     */
    if (event.delta > 0)
        zoom *= 0.9;
    else
        zoom *= 1.1;

    zoom = constrain(zoom, 0.2, 20);    // limite entre une valeur minimale et maximale (limite le zoom entre 0.2 et 20)
}

function draw() {
    background(0);                      // fond de couleur noir

    translate(width / 2, height / 2);   // définit le centre du canva (par défaut, le centre est le coin supérieur gauche, ici, il est fixé au centre (largeur/2 et hauteur/2))
    scale(zoom);                        // met à l'échelle le système de coordonnées selon le paramètre donné (ici, il s'agit de zoom)

    dessinerSoleil();
    dessinerOrbites();
    dessinerPlanetes();

    // Gestion des affichages du cadre "Informations"
    const tempsEl = document.getElementById("temps");
    if (tempsEl)
        tempsEl.textContent = indexAnimation;

    const nbPlanetesEl = document.getElementById("nbPlanetes");
    if (nbPlanetesEl)
        nbPlanetesEl.textContent = Object.keys(trajectoires).length;

    // Continue l'avancée des planètes tant que le bouton "pause" n'est pas enclenché
    if (animationActive)
        indexAnimation++;
}