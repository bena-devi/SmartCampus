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


// Sample Data (tum backend se bhi laa sakte ho)

// Show All Resources
function showResources() {
    let list = document.getElementById("dataList");
    list.innerHTML = "";

    resources.forEach(res => {
        let li = document.createElement("li");
        li.innerHTML = `${res.name} (${res.type}) - 
            ${res.booked ? "Booked" : "Available"}`;
        list.appendChild(li);
    });
}

// Show Only Available Resources
function showAvailable() {
    let list = document.getElementById("dataList");
    list.innerHTML = "";

    let available = resources.filter(res => !res.booked);

    available.forEach(res => {
        let li = document.createElement("li");
        li.innerHTML = `${res.name} (${res.type}) - Available`;
        list.appendChild(li);
    });
}

// Show Booked Resources
function showBooking() {
    let list = document.getElementById("dataList");
    list.innerHTML = "";

    let booked = resources.filter(res => res.booked);

    booked.forEach(res => {
        let li = document.createElement("li");
        li.innerHTML = `${res.name} (${res.type}) - Booked by ${res.user}`;
        list.appendChild(li);
    });
}

// Logout
function logout() {
    alert("Logged out!");
    window.location.href = "index.html";
}






// Logout
function logout() {
    alert("Logged out!");
    window.location.href = "index.html";
}


