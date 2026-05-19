const container = document.getElementById("main-editor-view");
const ghostBlock = document.getElementById("ghost-block");
let highestZIndex = 1010;

function makeElementDraggable(element, initialEvent) {
  if (initialEvent.target.tagName === 'SELECT' || initialEvent.target.closest('select') || initialEvent.target.tagName === 'INPUT' || initialEvent.target.closest('input')) {
    return;
  }

  highestZIndex++;
  element.style.zIndex = highestZIndex;

  const containerRect = container.getBoundingClientRect();

  if (element.parentNode !== container) {
    const originalRect = element.getBoundingClientRect();
    
    element.style.position = "absolute";
    element.style.margin = "0";
    element.style.left = `${originalRect.left - containerRect.left}px`;
    element.style.top = `${originalRect.top - containerRect.top}px`;
    
    container.appendChild(element);
  }

  const rect = element.getBoundingClientRect();
  const offsetX = initialEvent.clientX - rect.left;
  const offsetY = initialEvent.clientY - rect.top;

  function updatePosition(clientX, clientY) {
    element.style.left = `${clientX - containerRect.left - offsetX}px`;
    element.style.top = `${clientY - containerRect.top - offsetY}px`;
  }

  function getPageRect(el) {
    const r = el.getBoundingClientRect();
    return {
      left: r.left + window.scrollX,
      right: r.right + window.scrollX,
      top: r.top + window.scrollY,
      bottom: r.bottom + window.scrollY
    };
  }

  function onMouseMove(e) {
    if (e.buttons !== 1) {
      onMouseUp(e);
      return;
    }

    updatePosition(e.clientX, e.clientY);

    if (ghostBlock) {
      const ghostRect = getPageRect(ghostBlock);

      if (
        e.pageX >= ghostRect.left &&
        e.pageX <= ghostRect.right &&
        e.pageY >= ghostRect.top &&
        e.pageY <= ghostRect.bottom
      ) {
        if (!element.classList.contains("o-block")) {
          ghostBlock.classList.add("glow");
        }
      } else {
        ghostBlock.classList.remove("glow");
      }
    }
  }

  function onMouseUp(e) {
    window.removeEventListener('mousemove', onMouseMove);
    window.removeEventListener('mouseup', onMouseUp);

    const sidebarRect = getPageRect(slidingWindow);

    if (
      e.pageX >= sidebarRect.left &&
      e.pageX <= sidebarRect.right &&
      e.pageY >= sidebarRect.top &&
      e.pageY <= sidebarRect.bottom
    ) {
      element.remove();
      playOverlap("trash");
      if (ghostBlock) {
        ghostBlock.classList.remove("glow");
      }
      return;
    }

    if (ghostBlock) {
      const ghostRect = getPageRect(ghostBlock);

      if (
        e.pageX >= ghostRect.left &&
        e.pageX <= ghostRect.right &&
        e.pageY >= ghostRect.top &&
        e.pageY <= ghostRect.bottom &&
        !element.classList.contains("o-block")
      ) {
        element.style.position = "relative";
        element.style.left = "";
        element.style.top = "";
        element.classList.remove("menu-block");
        element.classList.remove("cloned-element");
        
        const targetBlocksContainer = (typeof blocks !== 'undefined') ? blocks : document.getElementById("blocks");
        
        if (targetBlocksContainer) {
          targetBlocksContainer.insertBefore(element, ghostBlock);
          playOverlap("drop");
        }
      }
      ghostBlock.classList.remove("glow");
    }
  }

  window.addEventListener('mousemove', onMouseMove);
  window.addEventListener('mouseup', onMouseUp);
}

const templates = document.querySelectorAll(".block-template");

templates.forEach(template => {
  template.addEventListener("mousedown", (e) => {
    if (e.target.tagName === 'SELECT' || e.target.closest('select') || e.target.tagName === 'INPUT' || e.target.closest('input')) {
      return; 
    }

    e.preventDefault();

    const clone = template.cloneNode(true);
    clone.classList.remove("block-template");
    clone.classList.add("cloned-element");
    
    clone.style.position = "absolute";
    clone.style.margin = "0";

    const containerRect = container.getBoundingClientRect();
    const templateRect = template.getBoundingClientRect();
    
    clone.style.left = `${templateRect.left - containerRect.left}px`;
    clone.style.top = `${templateRect.top - containerRect.top}px`;
    
    clone.innerHTML += revealFullBlock(String(clone.id));
    clone.removeAttribute("id");

    container.appendChild(clone);

    clone.addEventListener('mousedown', (cloneEvent) => {
      if (cloneEvent.target.tagName === 'SELECT' || cloneEvent.target.closest('select') || cloneEvent.target.tagName === 'INPUT' || cloneEvent.target.closest('input')) {
        return; 
      }

      cloneEvent.stopPropagation(); 
      cloneEvent.preventDefault();
      makeElementDraggable(clone, cloneEvent); 
    });

    makeElementDraggable(clone, e);
  });
});

const items = document.querySelectorAll('.draggable-item');
items.forEach(item => {
  item.addEventListener('mousedown', (e) => {
    if (e.target.tagName === 'SELECT' || e.target.closest('select') || e.target.tagName === 'INPUT' || e.target.closest('input')) {
      return; 
    }

    e.preventDefault();
    makeElementDraggable(item, e);
  });
});