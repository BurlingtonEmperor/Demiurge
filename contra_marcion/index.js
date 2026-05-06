const toggleBtn = document.getElementById('block-menu-toggle');
const slidingWindow = document.getElementById('sliding-window');

const swLeader = document.getElementById("sw-leader");

toggleBtn.addEventListener('click', () => {
  slidingWindow.classList.toggle('open'); 
});

swLeader.style.marginTop = String(toggleBtn.offsetHeight + 15) + "px";