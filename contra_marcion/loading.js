document.addEventListener("DOMContentLoaded", () => {
  const loadingScreen = document.getElementById("app-loading-screen");
  if (loadingScreen) {
    loadingScreen.classList.add("loaded");
  }
});