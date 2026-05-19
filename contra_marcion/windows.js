let minZIndex = 2000;

function makeWindowDraggable(element, initialEvent) {
  const ignoredTags = ['INPUT', 'SELECT', 'TEXTAREA', 'BUTTON', 'A'];
  if (ignoredTags.includes(initialEvent.target.tagName) || initialEvent.target.closest('button')) {
    return;
  }

  const rect = element.getBoundingClientRect();
  const offsetX = initialEvent.clientX - rect.left;
  const offsetY = initialEvent.clientY - rect.top;

  if (window.highestZIndex === undefined) window.highestZIndex = minZIndex;
  window.highestZIndex++;
  element.style.zIndex = window.highestZIndex;

  function onMouseMove(e) {
    let newX = e.clientX - offsetX;
    let newY = e.clientY - offsetY;

    const maxX = window.innerWidth - rect.width;
    const maxY = window.innerHeight - rect.height;
    
    newX = Math.max(0, Math.min(newX, maxX));
    newY = Math.max(0, Math.min(newY, maxY));

    element.style.left = `${newX}px`;
    element.style.top = `${newY}px`;
  }

  function onMouseUp() {
    window.removeEventListener('mousemove', onMouseMove);
    window.removeEventListener('mouseup', onMouseUp);
  }

  window.addEventListener('mousemove', onMouseMove);
  window.addEventListener('mouseup', onMouseUp);
}