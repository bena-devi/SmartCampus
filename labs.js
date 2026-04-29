window.onload = function () {
    loadLabs();
};

// Add Labs
function addLab() {
    let input = document.getElementById("labInput");
    let value = input.value.trim();

    if (value === "") {
        alert("Enter lab name");
        return;
    }

    let labs = JSON.parse(localStorage.getItem("labs")) || [];
    labs.push(value);

    localStorage.setItem("labs", JSON.stringify(labs));

    input.value = "";
    loadLabs();
}


function loadLabs() {
    let labs = JSON.parse(localStorage.getItem("labs")) || [];
    let list = document.getElementById("labList");
    let count = document.getElementById("labCount");

    list.innerHTML = "";
    count.textContent = labs.length;

    labs.forEach((lab, index) => {
        let li = document.createElement("li");

        li.innerHTML = `
            <span class="name">{lab}</span>
            <div class="actions">
                <button class="edit" onclick="editLab(${index})">Edit</button>
                <button class="delete" onclick="deleteLab(${index})">Cancel</button>
            </div>
        `;

        list.appendChild(li);
    });
}

function deleteLab(index) {
    let labs = JSON.parse(localStorage.getItem("labs")) || [];
    labs.splice(index, 1);
    localStorage.setItem("labs", JSON.stringify(labs));
    loadLabs();
}


function editLab(index) {
    let labs = JSON.parse(localStorage.getItem("labs")) || [];
    let newName = prompt("Edit Lab Name:", labs[index]);

    if (newName && newName.trim() !== "") {
        labs[index] = newName;
        localStorage.setItem("labs", JSON.stringify(labs));
        loadLabs();
    }
}


function searchLab() {
    let input = document.getElementById("searchBox").value.toLowerCase();
    let items = document.querySelectorAll("#labList li");

    items.forEach(item => {
        let text = item.querySelector(".name").textContent.toLowerCase();
        item.style.display = text.includes(input) ? "flex" : "none";
    });
}


function goBack() {
    window.history.back();
}