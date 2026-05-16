/*
Houses all basic interactions
*/

const toggleBtn = document.getElementById('block-menu-toggle');
const slidingWindow = document.getElementById('sliding-window');

const swLeader = document.getElementById("sw-leader");
const bHeader = document.getElementById("b-header");
const mlHeader = document.getElementById("ml-header");
const vHeader = document.getElementById("v-header");
const oHeader = document.getElementById("o-header");
const mHeader = document.getElementById("m-header");

toggleBtn.addEventListener('click', () => {
  slidingWindow.classList.toggle('open'); 
});

swLeader.style.marginTop = String(toggleBtn.offsetHeight + 15) + "px";

const blocks = document.getElementById("blocks");
blocks.style.left = String(toggleBtn.offsetLeft * 30) + "px";

const aiSection = document.getElementById("ai-section");
const bSection = document.getElementById("b-section");
const mlSection = document.getElementById("ml-section");
const vSection = document.getElementById("v-section");
const oSection = document.getElementById("o-section");
const mSection = document.getElementById("m-section");

swLeader.onclick = function () {
  aiSection.scrollIntoView({
    behavior: 'smooth', 
    block: 'start'      
  });
}

mlHeader.onclick = function () {
  mlSection.scrollIntoView({
    behavior: 'smooth', 
    block: 'start'      
  });
}

vHeader.onclick = function () {
  vSection.scrollIntoView({
    behavior: 'smooth', 
    block: 'start'      
  });
}

oHeader.onclick = function () {
  oSection.scrollIntoView({
    behavior: 'smooth', 
    block: 'start'      
  });
}

mHeader.onclick = function () {
  mSection.scrollIntoView({
    behavior: 'smooth', 
    block: 'start'      
  });
}

bHeader.onclick = function () {
  bSection.scrollIntoView({
    behavior: 'smooth', 
    block: 'start'  
  });
}