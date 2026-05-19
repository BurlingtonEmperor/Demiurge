const aiModelBlock_preset = document.querySelectorAll('.ai-block.block-template');
aiModelBlock_preset.forEach((element, index) => {
  element.id = `ai-block-${index}`;
});

const basicModelBlock_preset = document.querySelectorAll('.basic-block.block-template');
basicModelBlock_preset.forEach((element, index) => {
  element.id = `basic-block-${index}`;
});

const variableModelBlock_preset = document.querySelectorAll('.v-block.block-template');
variableModelBlock_preset.forEach((element, index) => {
  element.id = `v-block-${index}`;
});

function revealFullBlock (block_id) {
  switch (block_id) {
    // AI BLOCK SECTION
    case "ai-block-0":
      return " <select name='ai-block-0'><option value='ask_once'>Ask Once</option><option value='Ask Everytime'>Ask Everytime</option></select>";
    case "ai-block-1":
      return " <select name='ai-block-1'><option value='gemini'>Gemini</option></select>";
    case "ai-block-2":
      return ": <input type='text' placeholder='Best fishing spots...'/> <select name='var-usage'><option value='text'>Text</option><option value='var'>Variables</option></select>";
    // BASIC BLOCK SECTION
    case "basic-block-0":
      return ": <input type='text' placeholder='Hello, World!'/> <select name='var-usage'><option value='text'>Text</option><option value='var'>Variables</option></select>";
    case "basic-block-1":
      return `: <input type='text' placeholder="Favorite color?"/> <select name='var-usage'><option value='text'>Text</option><option value='var'>Variables</option></select>`;
    case "basic-block-4":
      return ": <input type='text' placeholder='This code runs well'/>";
    case "basic-block-5":
      return " <input type='number' placeholder='1' class='small-width'/> seconds";
    // VARIABLE BLOCK SECTION
    case "v-block-0":
    case "v-block-1":
    case "v-block-2":
      return ", name: <input type='text' placeholder='x' class='small-width'/>, value: <input type='number' placeholder='5' class='small-width'/>";
    case "v-block-3":
      return ", name: <input type='text' placeholder='x' class='small-width'/>, value: <select name='boolean'><option value='true'>True</option><option value='false'>False</option></select>";
    case "v-block-4":
      return ", name: <input type='text' placeholder='x' class='small-width'/>, value: <input type='number' placeholder='This is a string'/>";
  }
  return "";
}