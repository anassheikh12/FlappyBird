let score = 0;
let y = 30; //y-axis of bird
let g = innerHeight / 4000; //gravity effect
let birdMotion;
let obsCreateMotion;
let gameOverFlag = false;
let obstacleIntervals = [];
let isPaused = false;

function createObstacle() {
    let upperHeight = 0;
    let lowerHeight = 0;
    upperHeight = 20 + Math.random() * 45;
    lowerHeight = 100 - upperHeight - 35;
    let upper = document.createElement("img")
    upper.setAttribute("src", "flappyBirdPipe.jpeg");
    upper.setAttribute("class", "obs");
    upper.style.height = upperHeight + "vh";
    let lower = document.createElement("img")
    lower.setAttribute("src", "flappyBirdPipe - down.jpeg");
    lower.setAttribute("class", "obs");
    lower.style.height = lowerHeight + "vh";
    lower.style.top = upperHeight + 35 + "vh";
    document.body.appendChild(upper)
    document.body.appendChild(lower)
    return [lower, upper, upperHeight]
}
birdMotion = setInterval(() => {
    if (!isPaused) {
        if (y < 90) {
            g += innerHeight / 20000;
            y += g;
            document.getElementById("bird").style.top = y + "vh";
        } else if (y >= 90 && !gameOverFlag) {
            gameOver();
        }
    }
}, 25);
obsCreateMotion = setInterval(() => {
    if (!isPaused) {
        obstacleMotion(createObstacle(), 100)
    }
}, 2500);

function obstacleMotion(elem, i) {
    let x = setInterval(() => {
        if (!isPaused) {
            i -= 0.25;
            if (i < 26 && i > 14 && !(y > elem[2] && y < elem[2] + 35) && !gameOverFlag) {
                gameOver();
            } else if (i < 5) {
                score++
                document.getElementsByTagName("span")[0].innerText = score
                elem[1].remove()
                elem[0].remove()
                clearInterval(x)
                obstacleIntervals = obstacleIntervals.filter(interval => interval !== x);
            }
            elem[0].style.left = i + "vw"
            elem[1].style.left = i + "vw"
        }
    }, 20)
    obstacleIntervals.push(x);
}
//making bird jump when click space
window.addEventListener("keydown", e => {
    if (e.code == "Space") {
        g = -innerHeight / 600
    }
})

window.addEventListener("click", () => {
        g = -innerHeight / 600
})

function gameOver() {
    gameOverFlag = true;
    clearInterval(birdMotion);
    clearInterval(obsCreateMotion);
    obstacleIntervals.forEach(interval => clearInterval(interval));
    obstacleIntervals = [];
    let gameOverMsg = document.createElement("span");
    gameOverMsg.innerText = "GAME OVER";
    gameOverMsg.style.position = "absolute";
    gameOverMsg.style.top = "35vh";
    gameOverMsg.style.left = "50%";
    gameOverMsg.style.transform = "translateX(-50%)";
    gameOverMsg.style.fontSize = "50px";
    gameOverMsg.style.color = "red";
    gameOverMsg.style.fontWeight = "bold";
    gameOverMsg.style.zIndex = "10";
    document.getElementsByTagName("div")[0].appendChild(gameOverMsg);
    let restartBtn = document.getElementById("restartBtn");
    restartBtn.style.display = "block";
    restartBtn.style.position = "absolute";
    restartBtn.style.top = "50vh";
    restartBtn.style.left = "50%";
    restartBtn.style.transform = "translateX(-50%)";
    restartBtn.style.padding = "15px 30px";
    restartBtn.style.fontSize = "24px";
    restartBtn.style.backgroundColor = "#4CAF50";
    restartBtn.style.color = "white";
    restartBtn.style.border = "none";
    restartBtn.style.borderRadius = "10px";
    restartBtn.style.cursor = "pointer";
    restartBtn.style.zIndex = "10";
}

function restartGame() {
    y = 30;
    g = innerHeight / 4000;
    score = 0;
    gameOverFlag = false;
    document.getElementById("bird").style.top = y + "vh";
    document.getElementsByTagName("span")[0].innerText = score;
    // Remove all obstacles
    let obstacles = document.querySelectorAll(".obs");
    obstacles.forEach(obs => obs.remove());
    // Remove game over message
    let gameOverMsgs = document.querySelectorAll("span");
    gameOverMsgs.forEach(span => {
        if (span.innerText === "GAME OVER") span.remove();
    });
    document.getElementById("restartBtn").style.display = "none";
    // Restart intervals
    birdMotion = setInterval(() => {
        if (y < 90) {
            g += innerHeight / 20000;
            y += g;
            document.getElementById("bird").style.top = y + "vh";
        } else if (y >= 90 && !gameOverFlag) {
            gameOver();
        }
    }, 25);
    obsCreateMotion = setInterval(() => {
        obstacleMotion(createObstacle(), 100)
    }, 2500);
}

document.getElementById("restartBtn").addEventListener("click", restartGame);

// Pause game when tab is not visible
document.addEventListener("visibilitychange", () => {
    if (document.hidden) {
        isPaused = true;
    } else {
        isPaused = false;
    }
});

let isAlerted = false
setInterval(()=>{
    if(screen.width<screen.height&&!isAlerted){
        isAlerted=true
        alert("please rotate your device for better experience")
    }
},200)


