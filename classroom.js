function addClassroom() {
    let input = document.getElementById("classroomInput");
    let value = input.value.trim();

    if (value === "") {
        alert("Enter classroom name");
        return;
    }

    let li = document.createElement("li");

    li.innerHTML = `
        <span class="name">${value}</span>
        <div class="actions">
            <button class="edit" onclick="editClassroom(this)">Edit</button>
            <button class="delete" onclick="deleteClassroom(this)">Cancel</button>
        </div>
    `;

    document.getElementById("classroomList").appendChild(li);
    input.value = "";
}

// Delete
function deleteClassroom(btn) {
    btn.parentElement.parentElement.remove();
}

// Edit
function editClassroom(btn) {
    let nameSpan = btn.parentElement.parentElement.querySelector(".name");
    let newName = prompt("Edit Classroom Name:", nameSpan.textContent);

    if (newName !== null && newName.trim() !== "") {
        nameSpan.textContent = newName;
    }
}

// Search
function searchClassroom() {
    let input = document.getElementById("searchBox").value.toLowerCase();
    let items = document.querySelectorAll("#classroomList li");

    items.forEach(item => {
        let text = item.querySelector(".name").textContent.toLowerCase();
        item.style.display = text.includes(input) ? "flex" : "none";
    });
}

// Back
function goBack() {
    window.history.back();
}