function showSection(sectionId) {
    let sections = document.querySelectorAll(".section");
    sections.forEach(sec => sec.classList.add("hidden"));

    document.getElementById(sectionId).classList.remove("hidden");
}

// Classroom
function addClassroom() {
    let input = document.getElementById("classroomInput");
    let value = input.value.trim();

    if(value === "") return;

    let li = document.createElement("li");
    li.innerHTML = `${value} <button class="delete-btn" onclick="this.parentElement.remove()">Cancel</button>`;

    document.getElementById("classroomList").appendChild(li);
    input.value = "";
}

// Lab
function addLab() {
    let input = document.getElementById("labInput");
    let value = input.value.trim();

    if(value === "") return;

    let li = document.createElement("li");
    li.innerHTML = `${value} <button class="delete-btn" onclick="this.parentElement.remove()">Cancel</button>`;

    document.getElementById("labList").appendChild(li);
    input.value = "";
}

// Logout
function logout() {
    alert("Logged out!");
    window.location.href = "index.html";
}


