const runButton = document.getElementById("run-me");

const terminal = document.getElementById("terminal");
const close_terminal = document.getElementById("close-terminal");
const terminal_output = document.getElementById("terminal-output");

const flagx = document.getElementById("flagx");
let is_running_html = 0;

runButton.onclick = function () {
  terminal.style.display = "block";

  terminal_output.innerHTML = "";

  const centerX = (window.innerWidth / 2) - (terminal.offsetWidth / 2);
  const centerY = (window.innerHeight / 2) - (terminal.offsetHeight / 2);
  
  terminal.style.left = `${centerX}px`;
  terminal.style.top = `${centerY}px`;
}

terminal.style.position = "absolute";
terminal.addEventListener('mousedown', (e) => {
  e.preventDefault(); 
  makeWindowDraggable(terminal, e);
});

close_terminal.onclick = function () {
  terminal.style.display = "none";
}

function escapeHTML (text) {
  if (text === null || text === undefined) return '';
  
  const map = {
    '&': '&amp;',
    '<': '&lt;',
    '>': '&gt;',
    '"': '&quot;',
    "'": '&#x27;',
    '/': '&#x2F;',
    '`': '&#x60;'
  };
  
  return String(text).replace(/[&<>"'`\/]/g, (character) => map[character]);
}

function addNewLine (line_content) {
  const safeLine = escapeHTML(line_content);
  terminal_output.innerHTML += "<div class='output-line'>" + String(safeLine) + "</div>";
}

function runFinal () {
  switch (String(flagx.value)) {
    case "default":
      switch (is_running_html) {
        case 1:
          break;
      }
      break;
  }
}